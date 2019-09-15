/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_object_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:22:45 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:22:46 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

void	*read_object_header(t_mach_o *file)
{
	struct mach_header	*mh;

	file->mh = NULL;
	file->mh_64 = NULL;
	if (check_file_addr_size(file,
							file->o_addr,
							sizeof(struct mach_header_64)) == -1)
		return (NULL);
	if (file->o_addr == NULL)
		return (NULL);
	mh = file->o_addr;
	if (mh->magic == MH_MAGIC || mh->magic == MH_CIGAM)
		file->mh = mh;
	else if (mh->magic == MH_MAGIC_64 || mh->magic == MH_CIGAM_64)
		file->mh_64 = (struct mach_header_64 *)mh;
	else
		return (NULL);
	return ((void *)mh);
}
