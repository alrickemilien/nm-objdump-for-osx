/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_endian.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:22:51 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:22:52 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

static uint32_t	revert_endian(uint32_t e)
{
	if (e == UNKNOWN_ENDIAN)
		return (e);
	if (e == LITTLE_ENDIAN)
		return (BIG_ENDIAN);
	return (LITTLE_ENDIAN);
}

uint32_t		read_object_endian(struct mach_header *header)
{
	uint32_t	host_endian;

	host_endian = endian();
	if (host_endian)
		host_endian = LITTLE_ENDIAN;
	else
		host_endian = BIG_ENDIAN;
	if (header->magic == MH_MAGIC || header->magic == MH_MAGIC_64)
		return (host_endian);
	else if (header->magic == MH_CIGAM || header->magic == MH_CIGAM_64)
		return (revert_endian(host_endian));
	return (UNKNOWN_ENDIAN);
}
