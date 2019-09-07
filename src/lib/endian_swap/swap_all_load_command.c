#include "mach_o.h"

#define NBR_SUPPORTED_LC 4

static const t_lc_swapper	g_swappers[NBR_SUPPORTED_LC] = {
	{swap_load_command_segment_32, LC_SEGMENT, 0},
	{swap_load_command_segment_64, LC_SEGMENT_64, 0},
	{swap_load_command_symtab, LC_SYMTAB, 0},
	{swap_load_command_symseg, LC_SYMSEG, 0},
};

static int32_t	check_lc_bound(t_mach_o *file,
									struct load_command *cur_lc)
{
	if (check_file_addr_size(file, cur_lc,
							sizeof(struct load_command)) == -1
		|| check_file_addr_size(file, cur_lc,
							cur_lc->cmdsize) == -1)
		return (-1);
	return (0);
}

static int32_t			swap_load_command(t_mach_o *file,
										struct load_command *lc)
{
	size_t	i;

	i = 0;
	lc->cmd = swap_int32(lc->cmd);
	lc->cmdsize = swap_int32(lc->cmdsize);
	if (check_lc_bound(file, lc) == -1)
	{
		dprintf(2, "Object file is malformed, "
			"the load commands would go beyond the end of the file\n");
		return (-1);
	}
	while (i < NBR_SUPPORTED_LC)
	{
		if (lc->cmd == g_swappers[i].cmd)
		{
			g_swappers[i].f(lc);
			return (0);
		}
		i++;
	}
	return (0);
}

int32_t					swap_all_load_commands(t_mach_o *file)
{
	size_t				i;
	struct mach_header	*hdr;
	struct load_command	*cur_lc;

	i = 0;
	if (file->mh)
		hdr = file->mh;
	else
		hdr = (struct mach_header *)file->mh_64;
	if (!hdr)
		return (-1);
	cur_lc = file->load_commands;
	while (i < hdr->ncmds)
	{
		if (swap_load_command(file, cur_lc) == -1)
			return (-1);
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (0);
}