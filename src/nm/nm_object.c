#include "nm.h"

int32_t	nm_object(t_mach_o *file, t_options *options)
{
	t_nm_process_info   nm_info;
	size_t  			i;
	t_symbol			*symbols;

	if (init_nm_process_info(file, &nm_info) == -1)
		return (0);
	if ((symbols = nm_get_symbols(file, &nm_info)) == NULL)
		return (-1);
	nm_sort_symbols(symbols, nm_info.st_lc->nsyms, options);
	i = 0;
	while (i < nm_info.st_lc->nsyms)
		nm_print_symbol(file, symbols + i++, &nm_info, options);
	free(symbols);
	cleanup_nm_process_info(&nm_info);
	return (0);
}