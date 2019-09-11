#include "nm.h"
#include <inttypes.h>

void	print_default_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c)
{
	if (info->symtab)
		printf("%08llx %c %s\n", symbol->sym_entry.n_value, c, (char *)symbol->string);
	else
		printf("%016llx %c %s\n", symbol->sym_entry.n_value, c, (char *)symbol->string);
}

void	print_unknown_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c)
{
	if (info->symtab)
		printf("         %c %s\n", c, (char *)symbol->string);
	else
		printf("                 %c %s\n", c, (char *)symbol->string);
}

void	print_hex_dump_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info)
{
	if (info->symtab)
		printf("%08llx %02x %02x %04x %08x %s\n",
				symbol->sym_entry.n_value,
				symbol->sym_entry.n_type,
				symbol->sym_entry.n_sect,
				symbol->sym_entry.n_desc,
				symbol->sym_entry.n_un.n_strx,
				(char *)symbol->string);
	else
		printf("%016llx %02x %02x %04x %08x %s\n",
				symbol->sym_entry.n_value,
				symbol->sym_entry.n_type,
				symbol->sym_entry.n_sect,
				symbol->sym_entry.n_desc,
				symbol->sym_entry.n_un.n_strx,
				(char *)symbol->string);
}