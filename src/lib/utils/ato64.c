/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:18:50 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:18:51 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

int64_t		ato64(const char *str)
{
	int64_t		nbr;
	int			is_neg;

	nbr = 0;
	is_neg = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		is_neg = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		nbr = nbr * 10 + *str++ - '0';
	if (is_neg)
		return (-nbr);
	return (nbr);
}
