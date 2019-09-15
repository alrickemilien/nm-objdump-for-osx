#include "nm.h"

static t_options_map options_map[] = {
		{ "a", ALL_SYMBOL, NULL },
		{ "P", POSIX, NULL },
		{ "g", ONLY_GLOBAL_SYMBOL, NULL },
		{ "n", SORT_NUMERIC, NULL },
		{ "o", PREPEND_FILE_ARCHIVE_NAME, NULL },
		{ "p", DO_NOT_SORT, NULL },
		{ "r", REVERSE_SORT, NULL },
		{ "u", ONLY_UNDEFINED_SYMBOL, NULL },
		{ "U", DO_NOT_DISPLAY_UNDEFINED_SYMBOL, NULL },
		{ "m", DISPLAY_NSECT, NULL },
		{ "x", DISPLAY_HEXA, NULL },
		{ "j", ONLY_SYMBOL_NAME, NULL },
		{ "l", LIST_PSEUDO_SYMBOL, NULL },
		{ "f", DISPLAY_DYNAMIC_LIB_SYMBOL, NULL },
		{ "A", DISPLAY_PATH_NAME, NULL },
		{ "P", DISPLAY_PORTABLE, NULL },
		{ "t", RADIX, NULL },// true
		{ "p", DO_NOT_SORT, NULL },
		{ "D", ONLY_DYNAMIC, NULL },
		{ "arch", ARCH_TYPE, &read_arch_option, },
		{ "s", SEGMENT_SECTION, NULL, },// true
		{ "print-size", PRINT_SIZE, NULL },
		{ "dynamic", ONLY_DYNAMIC, NULL },
		{ "size-sort", SORT_SIZE, NULL },
		{ "print-file-name", PREPEND_FILE_ARCHIVE_NAME, NULL },
		{ "undefined-only", ONLY_UNDEFINED_SYMBOL, NULL, },
		{ "no-sort", DO_NOT_SORT, NULL },
		{ "reverse-sort", REVERSE_SORT, NULL },
		{ "print-after-all", PRINT_AFTER_ALL, NULL },
		{ "print-before-all", PRINT_BEFORE_ALL, NULL },
		{ "just-symbol-name", ONLY_SYMBOL_NAME, NULL },
		{ "extern-only", ONLY_GLOBAL_SYMBOL, NULL },
		{ "defined-only", DEFINED_ONLY, NULL },
		{ "synthetic", DEFINED_ONLY, NULL },
		{ "radix", RADIX, &read_radix_option },
		{ NULL, 0, NULL },
};

/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

static int handle_option(
	t_options *options,
	t_options_map **last,
	const char *name)
{
	size_t j;
	size_t len;

	len = ft_strlen(name);
	j = 0;
	while (options_map[j].name != NULL)
	{
		if (!ft_strcmp(name, options_map[j].name)
			&& len == ft_strlen(options_map[j].name))
		{
			if (((int*)options)[options_map[j].offset] == 1)
				return (mach_o_error(-1, 
					"for the -%s option: may only occur zero or one times!\n",
					options_map[j].name));
			
			if (!options_map[j].waiting_for_value)
				((int*)options)[options_map[j].offset] = 1;

			// Handle value option like --arch x86_64
			else
				*last = &options_map[j];

			return (0);
		}

		j++;
	}

	mach_o_error(-1, "Unknown command line argument '%s'\n", name);

	return (-1);
}

/*
** Read args by filling t_options structure with 0 or 1
** list is the list of files passed as parameter
*/

int read_options_arguments(int ac, char **av, t_options *options)
{
	int	i;
	int	ret;
	int	error;
	t_options_map *last;

	ft_memset(options, 0, sizeof(t_options));

	error = 0;
	options->file_count = 0;
	last = NULL;
	i = 1;
	while (i < ac)
	{
		ret = 0;

		if (options->end_index)
			options->file_count += 1;

		// Handle when the arg before was waiting for value
		else if (last)
		{
			ret = last->waiting_for_value(options, av[i]);
			last = NULL;
		}
		
		// When the argument is '--', it means end arguments
		else if (is_a_end_arguments_string(av[i]))
			options->end_index = i;
		// Handle option like -p -dynamic or --dynamic
		else if (is_a_single_option(av[i]))
			ret = handle_option(options, &last, av[i] + 1);
		else if (is_a_multi_option(av[i]))
			ret = handle_option(options, &last, av[i] + 2);
		else
			options->file_count += 1;

		if (ret != 0)
			error = ret;

		i++;
	}

	return (error);
}
