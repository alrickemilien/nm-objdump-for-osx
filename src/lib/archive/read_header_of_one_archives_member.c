/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header_of_one_archives_member.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:24:01 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/14 18:24:02 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int	read_header_of_one_archives_member(t_mach_o *file)
{
	uint8_t	*member_header_addr;

	member_header_addr = (uint8_t *)file->archive_member_header_addr;
	if (check_archive_addr_size(file, member_header_addr, 60) == -1)
		return (-1);
	if (read_archive_member_name(file) == -1)
		return (-1);
	file->archive_member_header.st_time = (uint8_t*)(member_header_addr + 16);
	file->archive_member_header.st_uid = ato16u((const char *)member_header_addr
												+ 28);
	file->archive_member_header.st_gid = ato16u((const char *)member_header_addr
												+ 34);
	file->archive_member_header.st_mode = ato16u_base(
		(const char *)member_header_addr + 40, "01234567");
	file->archive_member_header.st_size = ato64(
		(const char *)member_header_addr + 48);
	if (file->archive_member_header.st_size < 0)
		return (mach_o_error(-1, "Invalid st_size in archive member\n"));
	return (0);
}
