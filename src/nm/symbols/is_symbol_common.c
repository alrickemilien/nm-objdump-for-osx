/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_common.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:09:49 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:09:49 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_common(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	if (!is_symbol_extern(symbol, nm_info))
		return (false);
	return (((symbol->sym_entry.n_type & N_TYPE) == N_UNDF)
			&& symbol->sym_entry.n_sect == NO_SECT
			&& symbol->sym_entry.n_value != 0);
}
