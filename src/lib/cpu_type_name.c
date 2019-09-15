/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_type_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:15:39 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:16:52 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"
#include <mach/machine.h>
#include <stddef.h>

/*
** Get identifier for cpu
** according to cpu type
*/

static const t_cpu_type_names	g_cpu_type_names[] = {
	{ CPU_TYPE_I386, "i386" },
	{ CPU_TYPE_X86_64, "x86_64" },
	{ CPU_TYPE_ARM, "arm" },
	{ CPU_TYPE_ARM64, "arm64" },
	{ 0, NULL }
};

const char						*cpu_type_name(
	cpu_type_t cpu_type)
{
	size_t	i;

	i = 0;
	while (g_cpu_type_names[i].cpu_name != NULL)
	{
		if (cpu_type == g_cpu_type_names[i].cputype)
			return (g_cpu_type_names[i].cpu_name);
		i++;
	}
	return ("unknown");
}
