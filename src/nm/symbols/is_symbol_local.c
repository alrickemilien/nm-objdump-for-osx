/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symbol_local.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:08:32 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:08:33 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

bool	is_symbol_local(t_symbol *symbol, t_mach_o_processor *nm_info)
{
	(void)nm_info;
	return (!(is_symbol_extern(symbol, nm_info)));
}
