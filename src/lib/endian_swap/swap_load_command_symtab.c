#include "mach_o.h"

void	swap_lc_symtab(struct load_command *lc)
{
	struct symtab_command	*sc;

	sc = (struct symtab_command *)lc;
	sc->symoff = swap_int32(sc->symoff);
	sc->nsyms = swap_int32(sc->nsyms);
	sc->stroff = swap_int32(sc->stroff);
	sc->strsize = swap_int32(sc->strsize);
}