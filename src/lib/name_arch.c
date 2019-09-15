/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_arch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:05:58 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 17:06:00 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

t_arch_map			g_arch_map[] = {
	{ "x86_64", CPU_TYPE_X86_64 },
	{ "x86-64", CPU_TYPE_X86_64 },
	{ "i386", CPU_TYPE_I386 },
	{ "ABI64", CPU_ARCH_ABI64 },
	{ "ppc", CPU_TYPE_POWERPC },
	{ "", -1 },
};

static const char	*g_default_name = "";

const char			*name_arch(int arch_type)
{
	size_t	i;

	i = 0;
	while (i * sizeof(t_arch_map) < sizeof(g_arch_map))
	{
		if (g_arch_map[i].value == arch_type)
			return (g_arch_map[i].name);
		i++;
	}
	return (g_default_name);
}
