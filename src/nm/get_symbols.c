#include "nm.h"

static void	read_symbol_32(t_symbol *symbol, struct nlist *nl)
{
	symbol->sym_entry.n_un.n_strx = nl->n_un.n_strx;
	symbol->sym_entry.n_type = nl->n_type;
	symbol->sym_entry.n_sect = nl->n_sect;
	symbol->sym_entry.n_desc = (uint16_t)nl->n_desc;
	symbol->sym_entry.n_value = (uint64_t)nl->n_value;
}

static void	read_symbol_64(t_symbol *symbol, struct nlist_64 *nl)
{
	symbol->sym_entry = *nl;
}

t_symbol	*get_symbols(
	t_mach_o *ofile,
	t_mach_o_processor *nm_info)
{
	t_symbol	*symbols;
	size_t		i;

	if (nm_info->st_lc == NULL
		|| (nm_info->symtab == NULL && nm_info->symtab_64 == NULL))
		return (NULL);
	if ((symbols = malloc(nm_info->st_lc->nsyms * sizeof(t_symbol))) == NULL)
		return (NULL);
	if (nm_info->st_lc->strsize)
		nm_info->string_table[nm_info->st_lc->strsize - 1] = 0;
	i = 0;
	while (i < nm_info->st_lc->nsyms)
	{
		if (nm_info->symtab)
			read_symbol_32(symbols + i, nm_info->symtab + i);
		else
			read_symbol_64(symbols + i, nm_info->symtab_64 + i);
		symbols[i].string = nm_get_string_table_entry(
			ofile, nm_info, symbols[i].sym_entry.n_un.n_strx, &symbols[i].len);
		i++;
	}
	return (symbols);
}
