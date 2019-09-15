/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_stab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:08:27 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:08:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_stab(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	(void)nm_info;
	return (((symbol->sym_entry.n_type & N_STAB)));
}
