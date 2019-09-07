#include "nm.h"

int32_t	nm_object(t_mach_o *file, t_options *options)
{
	t_mach_o_processor  info;
	size_t  			i;
	t_symbol			*symbols;

	if (init_processor_info(file, &nm_info) == -1)
		return (0);
	if ((symbols = get_symbols(file, &nm_info)) == NULL)
		return (-1);
	sort_symbols(symbols, nm_info.st_lc->nsyms, options);
	i = 0;
	while (i < nm_info.st_lc->nsyms)
		print_symbol(file, symbols + i++, &nm_info, options);
	free(symbols);
	cleanup_process_info(&nm_info);
	return (0);
}