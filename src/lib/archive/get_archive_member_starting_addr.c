/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_archive_member_starting_addr.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:29:14 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/14 18:29:15 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

void		*get_archive_member_starting_addr(t_mach_o *file)
{
	uint8_t		*addr;

	if (!file->archive_start_addr || !file->archive_member_header_addr)
		return (NULL);
	addr = ((uint8_t *)file->archive_member_header_addr + 60
		+ (file->archive_member_header.long_name
		? ((uint64_t)file->archive_member_header.name_length | 0x4)
		: 0));
	return ((uint8_t *)addr);
}
