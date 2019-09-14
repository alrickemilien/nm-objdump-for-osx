#include "mach_o.h"

uint32_t	count_sections_64(t_mach_o *file)
{
	struct load_command	*cur_lc;
	uint32_t			i;
	uint32_t			nsects;
	uint32_t			ncmds;

	if (file->mh == NULL && file->mh_64 == NULL)
		return (0);
	cur_lc = file->load_commands;
	i = 0;
	nsects = 0;
	ncmds = file->mh ? file->mh->ncmds : file->mh_64->ncmds;
	while (i < ncmds)
	{
		if (cur_lc->cmd == LC_SEGMENT_64)
			nsects += ((struct segment_command_64 *)(void *)cur_lc)->nsects;
		cur_lc = (struct load_command *)(void *)((uint8_t *)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (nsects);
}

static uint32_t		fill_sections_from_segment(struct load_command *lc,
										struct section_64 **secs,
										uint32_t count)
{
	uint32_t					i;
	struct segment_command_64	*sc;

	i = 0;
	sc = (struct segment_command_64 *)(void *)lc;
	while (i < sc->nsects)
		secs[count++] = (struct section_64*)(sc + 1) + i++;
	return (count);
}

struct section_64	**read_sections_64(t_mach_o *file,
											uint32_t *return_nsects)
{
	size_t				i;
	uint32_t			nsects;
	struct section_64	**secs;
	struct load_command	*cur_lc;

	i = 0;
	if (!file || !file->load_commands)
		return (NULL);
	*return_nsects = 0;
	nsects = count_sections_64(file);
	if ((secs = malloc(sizeof(struct section_64 *) * nsects)) == NULL)
		return (NULL);
	cur_lc = file->load_commands;
	while (i < nsects)
	{
		if (cur_lc->cmd == LC_SEGMENT_64)
			i = fill_sections_from_segment(cur_lc, secs, i);
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
	}
	*return_nsects = nsects;
	return (secs);
}
