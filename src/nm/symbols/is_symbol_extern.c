#include "nm.h"

bool	is_symbol_extern(t_symbol *symbol, t_mach_o_processor *info)
{
	(void)info;
	// ft_printf("symbol->sym_entry.n_type : %d\n", symbol->sym_entry.n_type);
	// ft_printf("symbol->sym_entry.n_type & N_EXT) : %d\n", symbol->sym_entry.n_type & N_EXT);

	return (!!(symbol->sym_entry.n_type & N_EXT));
}
