/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_segments_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:45:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 12:45:29 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

uint32_t				count_segments_32(t_mach_o *file)
{
	struct load_command *cur_lc;
	uint32_t			i;
	uint32_t			nsegs;
	uint32_t			ncmds;

	if ((!file->mh && !file->mh_64) || !file->load_commands)
		return ((uint32_t)-1);
	i = 0;
	nsegs = 0;
	cur_lc = file->load_commands;
	ncmds = file->mh ? file->mh->ncmds : file->mh_64->ncmds;
	while (i < ncmds)
	{
		if (cur_lc->cmd == LC_SEGMENT)
			nsegs++;
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (nsegs);
}

static int				fill_segments(struct segment_command **segs,
								uint32_t nsegs,
								t_mach_o *file)
{
	struct load_command	*cur_lc;
	uint32_t			i;
	uint32_t			ncmds;

	if ((!file->mh && !file->mh_64) || !file->load_commands)
		return (-1);
	i = 0;
	ncmds = file->mh ? file->mh->ncmds : file->mh_64->ncmds;
	cur_lc = file->load_commands;
	while (i < nsegs)
	{
		if (cur_lc->cmd == LC_SEGMENT)
			segs[i++] = (struct segment_command*)(void*)cur_lc;
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
	}
	return (0);
}

struct segment_command	**read_segments_32(t_mach_o *file,
											uint32_t *return_nsegs)
{
	uint32_t				nsegs;
	struct segment_command	**segs;

	if ((!file->mh && !file->mh_64) || !file->load_commands)
		return (NULL);
	if ((nsegs = count_segments_32(file)) == (uint32_t)-1)
		return (NULL);
	*return_nsegs = 0;
	if ((segs = malloc(sizeof(struct segment_command *) * nsegs)) == NULL)
		return (NULL);
	fill_segments(segs, nsegs, file);
	*return_nsegs = nsegs;
	return (segs);
}
