#include "mach_o.h"

void		swap_load_command_symseg(struct load_command *lc)
{
	struct symseg_command	*sc;

	sc = (struct symseg_command*)lc;
	sc->offset = swap_int32(sc->offset);
	sc->size = swap_int32(sc->size);
}