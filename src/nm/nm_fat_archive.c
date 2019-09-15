/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:15:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:15:42 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <mach-o/arch.h>

int32_t			find_current_arch(
	t_mach_o *file, t_options *options)
{
	if (file->arch_type == OBJECT_FILE)
		return (nm_object(file, options));
	else if (file->arch_type == FAT_FILE)
		return (nm_fat_archive(file, options));
	else if (file->arch_type == ARCHIVE_FILE)
		return (nm_archive(file, options));
	return (-1);
}

static int32_t	nm_all_fat_archs(
	t_mach_o *file, t_options *options)
{
	size_t	i;

	i = 0;
	while (i < file->fat_header->nfat_arch)
	{
		if (load_fat_archive_nth_arch(file, i) == -1)
		{
			i++;
			continue ;
		}
		if (file->fat_header->nfat_arch != 1)
			ft_printf("\n%s (for architecture %s):\n", file->path,
			cpu_type_name(file->fat_archs ? file->fat_archs[i].cputype
			: file->fat_archs_64[i].cputype));
		else
			ft_printf("%s:\n", file->path);
		if (find_current_arch(file, options) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int32_t			nm_fat_archive(
	t_mach_o *file, t_options *options)
{
	int32_t				narch_for_arch;
	const NXArchInfo	*host_arch;

	host_arch = NXGetLocalArchInfo();
	if ((narch_for_arch = find_fat_archive_architecture(file,
		host_arch->cputype | CPU_ARCH_ABI64, host_arch->cpusubtype)) == -1)
		return (nm_all_fat_archs(file, options));
	else if (!options->arch_type
	|| (options->arch_type == file->fat_archs[narch_for_arch].cputype))
	{
		if (load_fat_archive_nth_arch(file, (uint32_t)narch_for_arch) == -1)
			return (-1);
		return (find_current_arch(file, options));
	}
	return (mach_o_error(-1,
		"file: %s does not contain architecture: %s.\n",
		file->path, name_arch(options->arch_type)));
}
