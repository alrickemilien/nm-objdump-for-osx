/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fat_archive_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:21:03 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:21:23 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int	load_fat_archive_file(t_mach_o *file,
		void *object_addr,
		uint64_t object_size)
{
	(void)object_addr;
	(void)object_size;
	if (!file->addr || (((struct fat_header *)file->addr)->magic != FAT_MAGIC
		&& ((struct fat_header *)file->addr)->magic != FAT_MAGIC_64
		&& ((struct fat_header *)file->addr)->magic != FAT_CIGAM
		&& ((struct fat_header *)file->addr)->magic != FAT_CIGAM_64))
		return (-1);
	file->fat_header = file->addr;
	file->fat_archs = NULL;
	file->fat_archs_64 = NULL;
	file->narch = ~0U;
	file->arch_type = UNKNOWN_FILE;
	if (file->fat_header->magic == FAT_MAGIC
			|| file->fat_header->magic == FAT_CIGAM)
		file->fat_archs = (struct fat_arch*)(file->fat_header + 1);
	else
		file->fat_archs_64 = (struct fat_arch_64*)
			(void *)(file->fat_header + 1);
	if (endian() != BIG_ENDIAN)
		return (swap_fat_archive_headers(file));
	return (0);
}
