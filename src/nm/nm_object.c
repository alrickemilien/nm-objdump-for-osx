/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:14:09 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:15:18 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	find_common_sections_indexes(t_mach_o_processor *info)
{
	info->text_nsect = find_section(info, SEG_TEXT, SECT_TEXT);
	info->data_nsect = find_section(info, SEG_DATA, SECT_DATA);
	info->bss_nsect = find_section(info, SEG_DATA, SECT_BSS);
	return (0);
}

static int	find_symbol_table(
		t_mach_o_processor *info,
		t_mach_o *file)
{
	if ((info->st_lc =
		((struct symtab_command *)
		find_load_command_by_command(file, LC_SYMTAB))) == NULL)
		return (0);
	info->dysym_lc =
		(struct dysymtab_command *)
		find_load_command_by_command(file, LC_DYSYMTAB);
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

void		cleanup_processor_info(t_mach_o_processor *info)
{
	free(info->secs);
	free(info->secs_64);
	free(info->segs_64);
	free(info->segs);
}

int			init_processor_info(
		t_mach_o *file,
		t_mach_o_processor *info)
{
	ft_memset(info, 0, sizeof(t_mach_o_processor));
	if (!file->mh && !file->mh_64)
		return (-1);
	if (file->mh)
	{
		info->secs = read_sections_32(file, &info->nsects);
		info->segs = read_segments_32(file, &info->nsegs);
	}
	else
	{
		info->secs_64 = read_sections_64(file, &info->nsects);
		info->segs_64 = read_segments_64(file, &info->nsegs);
	}
	if (find_common_sections_indexes(info))
		return (-1);
	return (find_symbol_table(info, file));
}

/*
** The object sent here has already been loaded
*/

int32_t		nm_object(t_mach_o *file, t_options *options)
{
	t_mach_o_processor	info;
	size_t				i;
	t_symbol			*symbols;

	if (init_processor_info(file, &info) == -1)
		return (-1);
	if (info.st_lc == NULL)
		return (0);
	if ((symbols = read_symbols(file, &info)) == NULL)
		return (-1);
	sort_symbols(symbols, info.st_lc->nsyms, options);
	i = 0;
	while (i < info.st_lc->nsyms)
		print_symbol(file, symbols + i++, &info, options);
	free(symbols);
	cleanup_processor_info(&info);
	return (0);
}
