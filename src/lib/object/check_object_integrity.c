#include "mach_o.h"

static const t_lc_integrity_check	g_map_lc_checkers[] = {
		{check_lc_segment_integrity, LC_SEGMENT},
		{check_lc_segment_64_integrity, LC_SEGMENT_64},
		{check_lc_symtab_integrity, LC_SYMTAB},
};

static int	check_lc_bound(t_mach_o *file,
									struct load_command *cur_lc)
{
	if (check_object_addr_size(file, cur_lc,
								sizeof(struct load_command)) == -1
		|| check_object_addr_size(file, cur_lc,
								cur_lc->cmdsize) == -1)
		return (-1);
	return (0);
}

static int			check_single_load_command_integrity(
    t_mach_o *file,
	struct load_command *lc)
{

	size_t    i;

	i = 0;
	while (i < sizeof(g_map_lc_checkers) / sizeof(t_lc_integrity_check))
	{
		if (lc->cmd == g_map_lc_checkers[i].cmd)
		{
			if (g_map_lc_checkers[i].f(file, lc) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int					check_load_commands_integrity(t_mach_o *file)
{
	size_t              i;
	struct mach_header	*hdr;
	struct load_command *cur_lc;

	i = 0;
	if (file->mh)
		hdr = file->mh;
	else
		hdr = (struct mach_header *)file->mh_64;
	cur_lc = file->load_commands;
	while (i < hdr->ncmds)
	{
		if (check_lc_bound(file, cur_lc) == -1)
		{
			dprintf(2, "Object file is malformed "
				"(the load commands would go beyond the end of the file)\n");
			return (-1);
		}
		if (check_single_load_command_integrity(file, cur_lc) == -1)
			return (-1);
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (0);
}

int32_t					check_object_integrity(t_mach_o *file)
{
	if (check_mach_header_integrity(file) == -1
		|| check_load_commands_integrity(file) == -1)
		return (-1);
	return (0);
}
