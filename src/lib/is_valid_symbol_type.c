#include "mach_o.h"

/*
 ** Values for N_TYPE bits of the n_type field.
** #define N_UNDF  0x0             // undefined, n_sect == NO_SECT
** #define N_ABS   0x2             // absolute, n_sect == NO_SECT
** #define N_SECT  0xe             // defined in section number n_sect
** #define N_PBUD  0xc             // prebound undefined (defined in a dylib)
** #define N_INDR  0xa             // indirect
*/

static const uint32_t g_symbol_type_map[] = {
	N_UNDF,
	N_ABS,
	N_SECT,
	N_PBUD,
	N_INDR,
	(uint32_t)-1,
};

bool is_valid_symbol_type(uint8_t n_type)
{
	size_t	i;

	i = 0;
	while (g_symbol_type_map[i] != (uint32_t)-1)
	{
		if (g_symbol_type_map[i] == n_type)
			return (true);
		i++;
	}

	return (false);
}
