#include "mach_o.h"

int	check_lc_segment_64_integrity(t_mach_o *file, struct load_command *lc)
{
	struct segment_command_64	*sc;

	sc = (struct segment_command_64 *)(void *)lc;
	if (sc->fileoff > file->o_size
		|| sc->fileoff + sc->filesize > file->o_size)
		return (mach_o_error(-1, "Truncated or malformed object"
				" (inconsistent filesize or fileoff in LC_SEGMENT_64)\n"));
	if (sc->nsects * sizeof(struct section_64)
		+ sizeof(struct segment_command_64) != lc->cmdsize)
		return (mach_o_error(-1, "Truncated or malformed object"
	    " (inconsistent cmdsize in LC_SEGMENT_64 for the number of sections)\n"));
	return (0);
}
