/*
** This file provides functions to get a display
** for a given symbol
*/

#include "nm.h"

/*
** From the man of nm
** U (undefined),
** A (absolute),
** T (text section symbol),
** D (data section symbol),
** B (bss section symbol),
** C  (common  symbol),  -  (for  debugger  symbol  table entries;  see -a below),
** S (symbol in a section other than those above),
** I (indirect symbol).
** If the symbol is local (non-external),
** the symbol's type is instead  represented by the corresponding lowercase  letter.
** A lower case u in a dynamic shared library indicates a undefined reference
** to a private external in another module in  the same library.
*/

typedef struct s_map_symbol_type_to_printable {
    uint8_t type;
    char    value;
} t_map_symbol_type_to_printable;

static const uint32_t g_symbol_type_map[] = {
	{N_UNDF, 'U'},

	{N_ABS, 'A'},

	{N_PBUD, 'u'},

	{N_INDR, 'I'},

	{(uint8_t)-1, 0},
};

int symbol_to_printable(struct nlist *symbol)
{
  size_t i;

  // Check basic cases into g_symbol_type_map
  i = 0;
  while (g_symbol_type_map[i].value != 0 ) {
    if (symbol->n_type == g_symbol_type_map[i].type)
      return (g_symbol_type_map[i].value);
    i++;
  }

  // Specific case with N_SECT
  // T (text section symbol),
  // D (data section symbol),
  // B (bss section symbol),
  // S

  // When no section is set
  if (symbol->n_sect === NO_SECT)


}
