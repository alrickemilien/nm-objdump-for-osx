/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:14:31 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:15:20 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

/*
** LITTLE ENDIAN MEANS LAST BYTE IS STORED AT FIRST
** little                          big
** 0x00 0xF0 0x00 0x00             0x00 0x00 0xF0 0x00
*/

uint64_t	endian(void)
{
	uint64_t	one;

	one = 1L;
	if (*((uint8_t*)(&one)) == 1)
		return (LITTLE_ENDIAN);
	return (BIG_ENDIAN);
}
