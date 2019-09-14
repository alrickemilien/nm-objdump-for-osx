/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_fat_archive_headers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:38:19 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/14 18:38:34 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

static void	swap_fat_header(struct fat_header *header)
{
	header->magic = swap_int32(header->magic);
	header->nfat_arch = swap_int32(header->nfat_arch);
}

static void	swap_fat_arch_32(struct fat_arch *fat_arch)
{
	fat_arch->cputype = (cpu_type_t)swap_int32(
		(uint32_t)fat_arch->cputype);
	fat_arch->cpusubtype = (cpu_subtype_t)swap_int32(
		(uint32_t)fat_arch->cpusubtype);
	fat_arch->offset = swap_int32(fat_arch->offset);
	fat_arch->size = swap_int32(fat_arch->size);
	fat_arch->align = swap_int32(fat_arch->align);
}

static void	swap_fat_arch_64(struct fat_arch_64 *fat_arch_64)
{
	fat_arch_64->cputype = (cpu_type_t)swap_int32(
		(uint32_t)fat_arch_64->cputype);
	fat_arch_64->cpusubtype = (cpu_subtype_t)swap_int32(
		(uint32_t)fat_arch_64->cpusubtype);
	fat_arch_64->offset = swap_int64(fat_arch_64->offset);
	fat_arch_64->size = swap_int64(fat_arch_64->size);
	fat_arch_64->align = swap_int32(fat_arch_64->align);
	fat_arch_64->reserved = swap_int32(fat_arch_64->reserved);
}

static int	swap_single_fat_archs_header(t_mach_o *file, uint32_t narch)
{
	if ((!file->fat_archs && !file->fat_archs_64)
		|| sizeof(file->fat_archs->cputype) != sizeof(int32_t)
		|| sizeof(file->fat_archs->cpusubtype) != sizeof(int32_t))
		return (-1);
	if (file->fat_archs)
		swap_fat_arch_32(&file->fat_archs[narch]);
	else
		swap_fat_arch_64(&file->fat_archs_64[narch]);
	return (0);
}

int			swap_fat_archive_headers(t_mach_o *file)
{
	size_t	i;

	if (!file->fat_header || (!file->fat_archs && !file->fat_archs_64))
		return (-1);
	swap_fat_header(file->fat_header);
	i = 0;
	while (i < file->fat_header->nfat_arch)
	{
		if ((file->fat_archs && check_file_addr_size(file,
										file->fat_archs + i,
										sizeof(struct fat_arch)) == -1)
			|| (file->fat_archs_64 && check_file_addr_size(file,
										file->fat_archs_64 + i,
										sizeof(struct fat_arch_64) == -1)))
			return (mach_o_error(2, "%s: Unknown file format", file->path));
		if (swap_single_fat_archs_header(file, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}
