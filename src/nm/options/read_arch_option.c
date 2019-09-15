/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arch_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:52:58 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:52:59 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_arch_option	g_arch_options[] = {
	{ "x86_64", 0 },
	{ "x86-64", 0 },
	{ "i386", 1 },
	{ "ppc", 2 },
	{ NULL, -1 },
};

int				read_arch_option(
	t_options *options, const char *value)
{
	size_t	i;
	size_t	len;

	if (value[0] == 0)
		return (-1);
	len = ft_strlen(value);
	i = 0;
	while (g_arch_options[i].name != NULL)
	{
		if (ft_strcmp(value, g_arch_options[i].name) == 0
				&& ft_strlen(g_arch_options[i].name) == len)
		{
			options->ARCH_TYPE = g_arch_options[i].value;
			return (0);
		}
		i++;
	}
	return (mach_o_error(-1,
	"for the -arch option: Unknown architecture named '%s'.\n", value));
}
