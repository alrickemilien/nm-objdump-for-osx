/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato16u_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:18:31 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:18:33 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"
#include <limits.h>

uint16_t		ato16u_base(
		const char *str,
		const char *base)
{
	uint16_t		nbr;
	uint16_t		base_len;
	char			*tmp;

	nbr = 0;
	base_len = ft_strlen(base);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	while (*str && (tmp = ft_strchr(base, *str)))
	{
		if ((uint16_t)(nbr * base_len + (uint16_t)tmp - (uint16_t)base) < nbr
				|| ((nbr > (uint16_t)USHRT_MAX / base_len)))
		{
			nbr = (uint16_t)USHRT_MAX;
			break ;
		}
		nbr = nbr * base_len + (uint16_t)tmp - (uint16_t)base;
		str++;
	}
	return (nbr);
}
