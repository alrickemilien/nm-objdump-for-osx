#include "nm.h"

bool	is_symbol_stab(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	(void)nm_info;
	return (((symbol->sym_entry.n_type & N_STAB)));
}
