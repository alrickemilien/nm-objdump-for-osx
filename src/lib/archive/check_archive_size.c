/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_archive_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:29:25 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/14 18:29:37 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int	check_archive_addr(t_mach_o *file, void *addr)
{
	if (file->archive_start_addr == NULL)
		return (-1);
	if (addr < file->archive_start_addr || addr < file->addr
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->archive_start_addr)
			> file->archive_size
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->addr) > file->file_size)
		return (-1);
	return (0);
}

int	check_archive_addr_size(t_mach_o *file,
								void *addr,
								uint64_t size)
{
	if (check_file_addr_size(file, addr, size) == 0
		&& check_archive_addr(file, addr) == 0
		&& check_archive_addr(file, (uint8_t*)addr + size) == 0)
		return (0);
	return (-1);
}
