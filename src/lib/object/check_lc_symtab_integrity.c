
#include "mach_o.h"

static int32_t	check_string_table_integrity(t_mach_o *file,
											struct symtab_command *sc)
{
	if (sc->stroff > file->o_size)
	{
		dprintf(2, "truncated or malformed object "
		"(stroff field of LC_SYMTAB command extends past the object file)\n");
		return (-1);
	}
	if (sc->stroff + sc->strsize > file->o_size)
	{
		dprintf(2, "truncated or malformed object "
		"(stroff field plus strsize field of LC_SYMTAB command"
		" extends past the end of the file)");
		return (-1);
	}
	return (0);
}

static int32_t	check_symtab_integrity(t_mach_o *file,
										struct symtab_command *sc)
{
	if (sc->symoff > file->o_size)
	{
		dprintf(2, "truncated or malformed object "
		"(symoff field of LC_SYMTAB command extends past the object file)\n");
		return (-1);
	}
	if (sc->symoff + sizeof(struct nlist) * sc->nsyms > file->o_size)
	{
		dprintf(2, "truncated or malformed object "
		"(symoff field plus nsyms field times sizeof(struct nlist)"
		" of LC_SYMTAB comand extends past the object file)\n");
		return (-1);
	}
	return (0);
}

int32_t			check_lc_symtab_integrity(t_mach_o *file,
											struct load_command *lc)
{
	struct symtab_command	*sc;

	sc = (struct symtab_command *)(void *)lc;
	if (sizeof(struct symtab_command) != sc->cmdsize)
	{
		dprintf(2, "Malformed object "
			"(LC_SYMTAB command has incorrect cmdsize)\n");
		return (-1);
	}
	if (check_string_table_integrity(file, sc) == -1
		|| check_symtab_integrity(file, sc) == -1)
		return (-1);
	return (0);
}