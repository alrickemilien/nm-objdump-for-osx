#include "mach_o.h"

uint32_t	count_segments_64(t_mach_o *file)
{
	struct load_command *cur_lc;
	uint32_t			i;
	uint32_t			nsegs;
	uint32_t			ncmds;

	// assert((file->mh || file->mh_64) && file->load_commands);
	i = 0;
	nsegs = 0;
	cur_lc = file->load_commands;
	ncmds = file->mh ? file->mh->ncmds : file->mh_64->ncmds;
	while (i < ncmds)
	{
		if (cur_lc->cmd == LC_SEGMENT_64)
			nsegs++;
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (nsegs);
}

static void					fill_segments(
	struct segment_command_64 **segs,
	uint32_t nsegs,
	t_mach_o *file)
{
	struct load_command	*cur_lc;
	size_t				i;
	uint32_t			ncmds;

	// assert((file->mh || file->mh_64) && file->load_commands);
	i = 0;
	ncmds = file->mh ? file->mh->ncmds : file->mh_64->ncmds;
	cur_lc = file->load_commands;
	while (i < nsegs)
	{
		if (cur_lc->cmd == LC_SEGMENT_64)
			segs[i++] = (struct segment_command_64*)(void*)cur_lc;
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
	}
}

struct segment_command_64	**read_segments_64(
	t_mach_o *file,
	uint32_t *return_nsegs)
{
	uint32_t					nsegs;
	struct segment_command_64	**segs;

	// assert((file->mh || file->mh_64) && file->load_commands);
	nsegs = count_segments_64(file);
	*return_nsegs = 0;
	if ((segs = malloc(sizeof(struct segment_command_64 *) * nsegs)) == NULL)
		return (NULL);
	fill_segments(segs, nsegs, file);
	*return_nsegs = nsegs;
	return (segs);
}
