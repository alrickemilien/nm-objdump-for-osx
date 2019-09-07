#include "nm.h"

static void		find_common_sections_indexes(t_mach_o_processor *info)
{
	info->text_nsect = find_section(info, SEG_TEXT, SECT_TEXT);
	info->data_nsect = find_section(info, SEG_DATA, SECT_DATA);
	info->bss_nsect = find_section(info, SEG_DATA, SECT_BSS);
}

static int32_t	find_symbol_table(
	t_mach_o_processor *info,
	t_mach_o *file)
{
	if (NULL == (info->st_lc = file_get_symbol_table_lc(file)))
		return (-1);
	info->dysym_lc = file_get_dynamic_symbol_table_lc(file);
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

int32_t	init_processor_info(
	t_mach_o *file,
	t_mach_o_processor *info)
{
	ft_bzero(info, sizeof(t_mach_o_processor));
	if (!file->mh && !file->mh_64)
		return (-1);
	if (file->mh)
	{
		info->secs = file_get_sections(file, &info->nsects);
		info->segs = file_get_segments(file, &info->nsegs);
	}
	else
	{
		info->secs_64 = file_get_sections_64(file, &info->nsects);
		info->segs_64 = file_get_segments_64(file, &info->nsegs);
	}
	find_common_sections_indexes(info);
	return (find_symbol_table(info, file));
}

int32_t	nm_object(t_mach_o *file, t_options *options)
{
	t_mach_o_processor  info;
	size_t  			i;
	t_symbol			*symbols;

	if (init_processor_info(file, &info) == -1)
		return (0);
	if ((symbols = get_symbols(file, &info)) == NULL)
		return (-1);
	sort_symbols(symbols, info.st_lc->nsyms, options);
	i = 0;
	while (i < info.st_lc->nsyms)
		print_symbol(file, symbols + i++, &info, options);
	free(symbols);
	cleanup_processor_info(&info);
	return (0);
}