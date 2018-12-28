
#define NBR_SUPPORTED_LC 4

static inline int32_t	check_lc_bound(t_ofile *ofile,
									struct load_command *cur_lc)
{
	if (-1 == ofile_object_check_addr_size(ofile, cur_lc,
									sizeof(struct load_command))
		|| -1 == ofile_object_check_addr_size(ofile, cur_lc,
									cur_lc->cmdsize))
		return (-1);
	return (0);
}

static int32_t			swap_load_command(t_ofile *ofile,
										struct load_command *lc)
{
	static const t_lc_swapper	swappers[NBR_SUPPORTED_LC] = {
		{swap_lc_segment, LC_SEGMENT, 0}, {swap_lc_symtab, LC_SYMTAB, 0},
		{swap_lc_symseg, LC_SYMSEG, 0}, {swap_lc_segment_64, LC_SEGMENT_64, 0},
	};
	uint32_t					i;

	i = 0;
	lc->cmd = swap_int32(lc->cmd);
	lc->cmdsize = swap_int32(lc->cmdsize);
	if (-1 == check_lc_bound(ofile, lc))
	{
		ft_dprintf(2, "Object file is malformed, "
			"the load commands would go beyond the end of the file\n");
		return (-1);
	}
	while (i < NBR_SUPPORTED_LC)
	{
		if (lc->cmd == swappers[i].cmd)
		{
			swappers[i].callback(lc);
			return (0);
		}
		i++;
	}
	return (0);
}

int32_t					swap_all_load_commands(t_ofile *ofile)
{
	uint32_t					i;
	struct mach_header			*hdr;
	struct load_command			*cur_lc;

	i = 0;
	if (ofile->mh)
		hdr = ofile->mh;
	else
		hdr = (struct mach_header *)ofile->mh_64;
	assert(hdr);
	cur_lc = ofile->load_commands;
	while (i < hdr->ncmds)
	{
		if (-1 == swap_load_command(ofile, cur_lc))
			return (-1);
		cur_lc = (struct load_command *)(void *)((uint8_t*)cur_lc
												+ cur_lc->cmdsize);
		i++;
	}
	return (0);
}