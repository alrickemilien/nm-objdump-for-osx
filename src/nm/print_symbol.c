#include "nm.h"

static const t_print_symbol_predicate	g_predicates[NCHARS_SYMBOLS] = {
		{is_symbol_extern_undefined, 'U', {0}}, {is_symbol_common, 'C', {0}},
		{is_symbol_extern_data, 'D', {0}}, {is_symbol_extern_text, 'T', {0}},
		{is_symbol_extern_bss, 'B', {0}}, {is_symbol_stab, '-', {0}},
		{is_symbol_extern_arbitrary_sect, 'S', {0}},
		{is_symbol_extern_indirect, 'I', {0}},
		{is_symbol_extern_absolute, 'A', {0}}, {is_symbol_undefined, 'u', {0}},
		{is_symbol_common, 'c', {0}}, {is_symbol_data, 'd', {0}},
		{is_symbol_text, 't', {0}}, {is_symbol_bss, 'b', {0}},
		{is_symbol_arbitrary_sect, 's', {0}}, {is_symbol_indirect, 'i', {0}},
		{is_symbol_absolute, 'a', {0}},
};

static char	get_symbol_char(t_symbol *symbol,
								t_mach_o_processor *info)
{

	size_t  i;

	i = 0;
	while (i < sizeof(g_predicates) / sizeof(*g_predicates))
	{
		if (g_predicates[i].predicate(symbol, info))
			return ((char)g_predicates[i].c);
		i++;
	}
	return ((char)-1);
}

static bool	should_print_symbol(t_symbol *symbol,
								t_mach_o_processor *info,
								t_options *options,
								char c)
{
	if (c == '-')
		return (false);
	if (flags->flags.bits.g && !is_symbol_extern(symbol, info))
		return (false);
	if (flags->flags.bits.u && !(c == 'u' || c == 'U'))
		return (false);
	if (flags->flags.bits.capital_u && (c == 'u' || c == 'U'))
		return (false);
	return (true);
}

void				nm_print_symbol(t_mach_o *file,
					t_symbol *symbol,
					t_mach_o_processor *info,
					t_options *options)
{
	char	c;

	(void)file;
	c = get_symbol_char(symbol, info);
	if (!((char)-1 != c))
		c = '?';
	if (!should_print_symbol(symbol, info, options, c))
		return ;
	if (flags->flags.bits.j || flags->flags.bits.u)
		printf("%s\n", (char *)sym->string);
	else if (flags->flags.bits.x)
		print_hexdump_symbol(symbol, info);
	else if (c == 'u' || c == 'U')
		print_undefined_symbol(symbol, info, c);
	else
		default_print_symbol(symbol, info, c);
}
