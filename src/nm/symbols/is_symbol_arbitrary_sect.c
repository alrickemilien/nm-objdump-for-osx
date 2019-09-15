/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_arbitrary_sect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:10:01 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:10:02 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_arbitrary_sect(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	if (is_symbol_extern(symbol, nm_info))
		return (false);
	return (((symbol->sym_entry.n_type & N_TYPE) == N_SECT)
			&& symbol->sym_entry.n_sect - 1 != nm_info->bss_nsect
			&& symbol->sym_entry.n_sect - 1 != nm_info->text_nsect
			&& symbol->sym_entry.n_sect - 1 != nm_info->data_nsect);
}
