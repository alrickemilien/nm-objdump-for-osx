/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_object_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:24:49 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:24:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

static int	read_object(t_mach_o *file)
{
	file->endian = read_object_endian(((struct mach_header *)file->o_addr));
	if (file->endian == UNKNOWN_ENDIAN)
		return (mach_o_error(-1, "Unknown endian found for object\n"));
	if (file->endian != endian())
		file->must_be_swapped = true;
	else
		file->must_be_swapped = false;
	if (read_object_header(file) == NULL)
		return (mach_o_error(-1, "Malformed object file, "
		"the mach-o header is truncated or non-existant\n"));
	if (read_object_load_commands(file) == NULL)
		return (mach_o_error(-1, "Malformed object file: no load commands\n"));
	return (0);
}

int			load_object_file(t_mach_o *file,
						void *object_addr,
						uint64_t object_size)
{
	file->o_addr = object_addr;
	file->o_size = object_size;
	if (check_file_addr_size(file,
					file->o_addr,
					file->o_size) == -1)
		return (-1);
	if (read_object(file) == -1)
		return (-1);
	if (file->must_be_swapped)
	{
		swap_object_header(file);
		if (swap_all_load_commands(file) == -1)
			return (-1);
	}
	if (check_object_integrity(file) == -1)
		return (-1);
	if (file->must_be_swapped)
		swap_symtab(file);
	return (0);
}
