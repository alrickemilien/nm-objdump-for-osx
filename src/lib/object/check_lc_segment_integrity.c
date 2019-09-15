/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lc_segment_integrity.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:30:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:30:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int	check_lc_segment_integrity(t_mach_o *file, struct load_command *lc)
{
	struct segment_command	*sc;

	sc = (struct segment_command *)(void *)lc;
	if (sc->fileoff > file->o_size
		|| sc->fileoff + sc->filesize > file->o_size)
		return (mach_o_error(2, "Truncated or malformed object"
		" (inconsistent filesize or fileoff in LC_SEGMENT)\n"));
	if (sc->nsects * sizeof(struct section)
		+ sizeof(struct segment_command) != lc->cmdsize)
		return (mach_o_error(2, "Truncated or malformed object"
		" (inconsistent cmdsize in LC_SEGMENT for the number of sections)\n"));
	return (0);
}
