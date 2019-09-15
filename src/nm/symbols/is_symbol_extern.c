/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_extern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:09:35 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:09:36 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_extern(t_symbol *symbol, t_mach_o_processor *info)
{
	(void)info;
	return (!!(symbol->sym_entry.n_type & N_EXT));
}
