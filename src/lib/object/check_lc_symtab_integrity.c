/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lc_symtab_integrity.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:29:10 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:29:53 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

static int	check_string_table_integrity(t_mach_o *file,
											struct symtab_command *sc)
{
	if (sc->stroff > file->o_size)
		return (mach_o_error(2, "truncated or malformed object "
		"(stroff field of LC_SYMTAB command extends past the object file)\n"));
	if (sc->stroff + sc->strsize > file->o_size)
		return (mach_o_error(2, "truncated or malformed object "
		"(stroff field plus strsize field of LC_SYMTAB command"
		" extends past the end of the file)"));
	return (0);
}

static int	check_symtab_integrity(t_mach_o *file,
										struct symtab_command *sc)
{
	if (sc->symoff > file->o_size)
		return (mach_o_error(2, "truncated or malformed object "
		"(symoff field of LC_SYMTAB command extends past the object file)\n"));
	if (sc->symoff + sizeof(struct nlist) * sc->nsyms > file->o_size)
		return (mach_o_error(2, "truncated or malformed object "
		"(symoff field plus nsyms field times sizeof(struct nlist)"
		" of LC_SYMTAB comand extends past the object file)\n"));
	return (0);
}

int			check_lc_symtab_integrity(t_mach_o *file,
											struct load_command *lc)
{
	struct symtab_command	*sc;

	sc = (struct symtab_command *)(void *)lc;
	if (sizeof(struct symtab_command) != sc->cmdsize)
		return (mach_o_error(2, "Malformed object "
		"(LC_SYMTAB command has incorrect cmdsize)\n"));
	if (check_string_table_integrity(file, sc) == -1
		|| check_symtab_integrity(file, sc) == -1)
		return (-1);
	return (0);
}
