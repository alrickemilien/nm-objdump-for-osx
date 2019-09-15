/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_radix_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:54:07 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:54:20 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

typedef struct	s_radix_option {
	char		*name;
	int			value;
}				t_radix_option;

t_radix_option	g_radix_options[] = {
	{ "o", 8 },
	{ "x", 16 },
	{ "d", 10 },
	{ NULL, -1 },
};

int				read_radix_option(
	t_options *options, const char *value)
{
	size_t	i;
	size_t	len;

	if (value[0] == 0)
		return (-1);
	len = ft_strlen(value);
	i = 0;
	while (g_radix_options[i].name != NULL)
	{
		if (ft_strcmp(value, g_radix_options[i].name) == 0
				&& ft_strlen(g_radix_options[i].name) == len)
		{
			options->RADIX = g_radix_options[i].value;
			return (0);
		}
		i++;
	}
	return (mach_o_error(-1,
	"for the -radix option: Cannot find the option named '%s'.\n", value));
}
