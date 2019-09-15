/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_load_command_by_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:14:19 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:14:20 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

/*
** This function returns the index of a specific load_command
** that corresponds to the uint32_t cmd given as parameter
*/

struct load_command	*find_load_command_by_command(
		t_mach_o *mach_o,
		uint32_t cmd)
{
	size_t				i;
	size_t				ncmds;
	struct load_command	*cursor_lc;

	if (NULL == mach_o->load_commands
		|| (NULL == mach_o->mh && NULL == mach_o->mh_64))
		return (NULL);
	i = 0;
	ncmds = mach_o->mh ? mach_o->mh->ncmds : mach_o->mh_64->ncmds;
	cursor_lc = mach_o->load_commands;
	while (i < ncmds)
	{
		if (check_object_addr_size(mach_o, cursor_lc,
				sizeof(struct load_command) == -1)
			|| check_object_addr_size(mach_o, cursor_lc,
				cursor_lc->cmdsize) == -1)
			return (NULL);
		if (cmd == cursor_lc->cmd
				|| (LC_REQ_DYLD | cmd) == cursor_lc->cmd)
			return (cursor_lc);
		cursor_lc = (struct load_command *)
			(void *)((uint8_t*)cursor_lc + cursor_lc->cmdsize);
		i++;
	}
	return (NULL);
}
