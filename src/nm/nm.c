/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:35:02 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:35:25 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	dispatch(t_mach_o *file, t_options *options)
{
	if (file->type == OBJECT_FILE)
		return (nm_object(file, options));
	else if (file->type == FAT_FILE)
		return (nm_fat_archive(file, options));
	else if (file->type == ARCHIVE_FILE)
		return (nm_archive(file, options));
	return (-1);
}

int			nm(t_options *options, const char *path)
{
	t_mach_o	file;
	int			error;

	ft_memset(&file, 0, sizeof(t_mach_o));
	if ((file.addr = map_loading_file(path, &file.file_size)) == NULL)
		return (-1);
	if (load_macho_file(&file, path, file.addr, file.file_size) < 0)
		return (mach_o_error(-1, NM_DEFAULT_MACHO_ERROR, file.path));
	if (file.type == UNKNOWN_FILE)
		return (mach_o_error(-1, "%s: %s Unknown file format\n", path, path));
	if (options->file_count > 1 && file.type == OBJECT_FILE)
		ft_printf("\n%s:\n", path);
	error = dispatch(&file, options);
	if (map_unloading_file(file.addr, file.file_size))
		return (-1);
	return (error);
}
