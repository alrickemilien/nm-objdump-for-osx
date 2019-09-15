/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_posix_dump_symbol.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:07:51 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 17:07:52 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <inttypes.h>

void	print_posix_dump_symbol(
		t_symbol *symbol,
		t_mach_o_processor *info,
		char c)
{
	if (info->symtab)
		ft_printf("%s %c %lx %lx\n",
				(char *)symbol->string,
				c,
				symbol->sym_entry.n_value,
				symbol->sym_entry.n_type & N_PEXT);
	else
		ft_printf("%s %c %llx %u\n",
				(char *)symbol->string,
				c,
				symbol->sym_entry.n_value,
				symbol->sym_entry.n_type & N_PEXT);
}
