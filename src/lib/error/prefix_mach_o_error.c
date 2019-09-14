/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_mach_o_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:41:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/14 18:42:28 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

static char	g_prefix[MAX_ERROR_BUFFER];

void		init_prefix_mach_o_error(const char *prefix)
{
	size_t	len;

	len = ft_strlen(prefix);
	if (len >= MAX_ERROR_BUFFER)
		len = MAX_ERROR_BUFFER - 1;
	ft_memset(g_prefix, 0, sizeof(g_prefix));
	memcpy(g_prefix, prefix, len * sizeof(char));
}

void		set_prefix_mach_o_error_to_buffer(char *buffer)
{
	memcpy(buffer, g_prefix, ft_strlen(g_prefix) * sizeof(char));
}
