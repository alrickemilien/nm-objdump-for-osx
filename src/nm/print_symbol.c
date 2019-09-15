/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:13:10 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:13:10 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static const t_print_symbol_predicate	g_predicates[NCHARS_SYMBOLS] = {
	{is_symbol_extern_unknown, 'U'}, {is_symbol_common, 'C'},
	{is_symbol_extern_data, 'D'}, {is_symbol_extern_text, 'T'},
	{is_symbol_extern_bss, 'B'}, {is_symbol_stab, '-'},
	{is_symbol_extern_arbitrary_sect, 'S'},
	{is_symbol_extern_indirect, 'I'},
	{is_symbol_extern_absolute, 'A'}, {is_symbol_unknown, 'u'},
	{is_symbol_common, 'c'}, {is_symbol_data, 'd'},
	{is_symbol_text, 't'}, {is_symbol_bss, 'b'},
	{is_symbol_arbitrary_sect, 's'}, {is_symbol_indirect, 'i'},
	{is_symbol_absolute, 'a'},
};

static char								read_symbol_char(
		t_symbol *symbol,
		t_mach_o_processor *info)
{
	size_t	i;

	i = 0;
	while (i < NCHARS_SYMBOLS)
	{
		if (g_predicates[i].predicate(symbol, info))
			return (g_predicates[i].c);
		i++;
	}
	return ((char)-1);
}

static bool								is_print_symbol_required(
		t_symbol *symbol,
		t_mach_o_processor *info,
		t_options *options,
		char c)
{
	if (c == '-')
		return (false);
	if (options->ONLY_GLOBAL_SYMBOL && !is_symbol_extern(symbol, info))
		return (false);
	if (options->ONLY_UNDEFINED_SYMBOL && !(c == 'u' || c == 'U'))
		return (false);
	if (options->DO_NOT_DISPLAY_UNDEFINED_SYMBOL && (c == 'u' || c == 'U'))
		return (false);
	return (true);
}

void									print_symbol(
		t_mach_o *file,
		t_symbol *symbol,
		t_mach_o_processor *info,
		t_options *options)
{
	char	c;

	(void)file;
	c = read_symbol_char(symbol, info);
	if (!((char)-1 != c))
		c = '?';
	if (!is_print_symbol_required(symbol, info, options, c))
		return ;
	if (options->ONLY_SYMBOL_NAME || options->ONLY_UNDEFINED_SYMBOL)
		ft_printf("%s\n", (char *)symbol->string);
	else if (options->DISPLAY_HEXA)
		print_hex_dump_symbol(symbol, info);
	else if (c == 'u' || c == 'U')
		print_unknown_symbol(symbol, info, c);
	else
		print_default_symbol(symbol, info, c);
}
