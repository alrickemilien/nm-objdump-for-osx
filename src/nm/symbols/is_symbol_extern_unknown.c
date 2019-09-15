/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_extern_unknown.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:08:46 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:08:47 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_extern_unknown(t_symbol *symbol, t_mach_o_processor *info)
{
	if (!is_symbol_extern(symbol, info))
		return (false);
	return (((symbol->sym_entry.n_type & N_TYPE) == N_UNDF)
			&& symbol->sym_entry.n_sect == NO_SECT
			&& symbol->sym_entry.n_value == 0);
}
