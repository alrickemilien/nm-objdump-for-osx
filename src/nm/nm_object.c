#include "nm.h"

static int	find_common_sections_indexes(t_mach_o_processor *info)
{
	info->text_nsect = find_section(info, SEG_TEXT, SECT_TEXT);
	info->data_nsect = find_section(info, SEG_DATA, SECT_DATA);
	info->bss_nsect = find_section(info, SEG_DATA, SECT_BSS);

	LOGDEBUG("info->text_nsect offset : %d\n"
		"info->data_nsect offset : %d\n"
		"info->bss_nsect offset : %d\n", 
		info->text_nsect,
		info->data_nsect,
		info->bss_nsect);

	return (0);
}

static int	find_symbol_table(
	t_mach_o_processor *info,
	t_mach_o *file)
{
	// printf(" JE SUIS LLLKKLKLKJL\n");
	if ((info->st_lc =
		((struct symtab_command *)find_load_command_by_command(file, LC_SYMTAB))) == NULL)
		return (-1);
	// printf("kakajsjdd\n");
	info->dysym_lc =
		(struct dysymtab_command *)find_load_command_by_command(file, LC_DYSYMTAB);
	if (file->mh)
	{
		info->symtab = (struct nlist *)(void *)((uint8_t*)file->o_addr
										+ info->st_lc->symoff);
		info->string_table = (uint8_t*)((uint8_t*)file->o_addr
										+ info->st_lc->stroff);
	}
	else
	{
		info->symtab_64 = (struct nlist_64 *)(void *)(
										(uint8_t*)file->o_addr
										+ info->st_lc->symoff);
		info->string_table = (uint8_t*)((uint8_t*)file->o_addr
										+ info->st_lc->stroff);
	}
	return (0);
}

void	cleanup_processor_info(t_mach_o_processor *info)
{
	free(info->secs);
	free(info->secs_64);
	free(info->segs_64);
	free(info->segs);
}

int	init_processor_info(
	t_mach_o *file,
	t_mach_o_processor *info)
{
	printf("OI 1\n");
	ft_memset(info, 0, sizeof(t_mach_o_processor));
	if (!file->mh && !file->mh_64)
		return (-1);
	printf("OI 2\n");

	if (file->mh)
	{
		printf("OI 3\n");

		LOGDEBUG("=> %d\n", 32);
		info->secs = read_sections_32(file, &info->nsects);
		info->segs = read_segments_32(file, &info->nsegs);
	}
	else
	{
		printf("OI 4\n");

		LOGDEBUG("=> %d\n", 64);
		info->secs_64 = read_sections_64(file, &info->nsects);
		info->segs_64 = read_segments_64(file, &info->nsegs);
	}
	printf("OI 5\n");
	
	if (find_common_sections_indexes(info))
		return (-1);
	printf("OI 6\n");
	return (find_symbol_table(info, file));
}

/*
** The object sent here has already been loaded
*/

int32_t	nm_object(t_mach_o *file, t_options *options)
{
	t_mach_o_processor  info;
	size_t  			i;
	t_symbol			*symbols;

	printf("O1\n");
	if (init_processor_info(file, &info) == -1)
		return (-1);
	printf("O2\n");
	if ((symbols = read_symbols(file, &info)) == NULL)
		return (-1);
	printf("O3\n");
	sort_symbols(symbols, info.st_lc->nsyms, options);
	printf("O4\n");
	i = 0;
	LOGDEBUG("info.st_lc->nsyms : %d\n", info.st_lc->nsyms);
	while (i < info.st_lc->nsyms)
		print_symbol(file, symbols + i++, &info, options);
	free(symbols);
	cleanup_processor_info(&info);
	return (0);
}