#include "nm.h"

bool	is_symbol_unknown(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	if (is_symbol_extern(symbol, nm_info))
		return (false);
	return (((symbol->sym_entry.n_type & N_TYPE) == N_UNDF)
			&& symbol->sym_entry.n_sect == NO_SECT
			&& symbol->sym_entry.n_value == 0);
}
