/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_load_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:22:32 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:22:36 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

struct load_command	*read_object_load_commands(t_mach_o *file)
{
	if (file->mh)
		file->load_commands = (struct load_command*)(file->mh + 1);
	else if (file->mh_64)
		file->load_commands = (struct load_command*)(file->mh_64 + 1);
	else
		return (NULL);
	if (check_file_addr_size(file,
		file->load_commands,
		sizeof(struct load_command)) == -1)
	{
		file->load_commands = NULL;
		return (NULL);
	}
	return (file->load_commands);
}
