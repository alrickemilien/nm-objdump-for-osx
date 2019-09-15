/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:25:10 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:25:25 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int32_t	check_object_addr(t_mach_o *file, void *addr)
{
	if (file->o_addr == NULL)
		return (-1);
	if (addr < file->o_addr
		|| addr < file->addr
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->o_addr)
		> file->o_size
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->addr)
		> file->file_size)
		return (-1);
	return (0);
}

int32_t	check_object_addr_size(t_mach_o *file,
		void *addr,
		uint64_t size)
{
	if (check_file_addr_size(file, addr, size) == 0
		&& check_object_addr(file, addr) == 0
		&& (size == 0
		|| check_object_addr(file, (uint8_t*)addr + size - 1) == 0))
		return (0);
	return (-1);
}
