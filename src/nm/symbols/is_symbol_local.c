#include "nm.h"

bool	is_symbol_local(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	(void)nm_info;
	return (!(is_symbol_extern(symbol, nm_info)));
}
