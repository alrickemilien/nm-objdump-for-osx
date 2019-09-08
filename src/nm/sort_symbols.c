#include "nm.h"

static bool		g_reverse_flag = 0;

static int		compare_syms(const void *a, const void *b)
{
	int	ret;

	ret = strcmp((char *)((const t_symbol*)a)->string,
					(char *)((const t_symbol*)b)->string);
	if (ret)
		return (g_reverse_flag ? -ret : ret);
	if (((const t_symbol*)a)->sym_entry.n_value
		< ((const t_symbol*)b)->sym_entry.n_value)
		return (g_reverse_flag ? 1 : -1);
	else if ((((const t_symbol*)a)->sym_entry.n_value
		> ((const t_symbol*)b)->sym_entry.n_value))
		return (g_reverse_flag ? -1 : 1);
	else
		return (0);
}

static int		compare_syms_n(const void *a, const void *b)
{
	if (((const t_symbol*)a)->sym_entry.n_value
		< ((const t_symbol*)b)->sym_entry.n_value)
		return (g_reverse_flag ? 1 : -1);
	else if ((((const t_symbol*)a)->sym_entry.n_value
		> ((const t_symbol*)b)->sym_entry.n_value))
		return (g_reverse_flag ? -1 : 1);
	if (((const t_symbol*)a)->sym_entry.n_type
		< ((const t_symbol*)b)->sym_entry.n_type)
		return (g_reverse_flag ? 1 : -1);
	else if ((((const t_symbol*)a)->sym_entry.n_type
		> ((const t_symbol*)b)->sym_entry.n_type))
		return (g_reverse_flag ? -1 : 1);
	else
		return (compare_syms(a, b));
}

void			sort_symbols(t_symbol *symbols,
								const uint64_t symbols_number,
								const t_options *options)
{
	if (options->p)
		return ;
	if (options->r)
		g_reverse_flag = 1;
	else
		g_reverse_flag = 0;
	if (options->n)
		sort((void *)symbols,
			symbols_number,
			sizeof(t_symbol),
			&compare_syms_n);
	else
	{
		sort((void*)symbols,
			symbols_number,
			sizeof(t_symbol),
			&compare_syms);
	}
}
