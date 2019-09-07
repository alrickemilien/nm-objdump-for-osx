#include "mach_o.h"

static const t_lc_swapper	g_swappers[NBR_SUPPORTED_LC] = {
	{swap_lc_segment, LC_SEGMENT, 0},
	{swap_lc_symtab, LC_SYMTAB, 0},
	{swap_lc_symseg, LC_SYMSEG, 0},
	{swap_lc_segment_64, LC_SEGMENT_64, 0},
};

static int32_t			swap_load_command(t_mach_o *file,
										struct load_command *lc)
{

	size_t	i;

	i = 0;
	lc->cmd = swap_int32(lc->cmd);
	lc->cmdsize = swap_int32(lc->cmdsize);
	if (check_lc_bound(file, lc)  == -1)
	{
		dprintf(2, "Object file is malformed, "
			"the load commands would go beyond the end of the file\n");
		return (-1);
	}
	while (i < NBR_SUPPORTED_LC)
	{
		if (lc->cmd == g_swappers[i].cmd)
		{
			g_swappers[i].callback(lc);
			return (0);
		}
		i++;
	}
	return (0);
}