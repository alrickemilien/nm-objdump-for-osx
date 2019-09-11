#include "nm.h"

/*
** This map regroups all options :
**  -a     Display all symbol table entries, including those inserted for use by debuggers.
**  -g     Display only global (external) symbols.
**  -n     Sort numerically rather than alphabetically.
**  -o     Prepend file or archive element name to each output line, rather than only once.
**  -p     Don't sort; display in symbol-table order.
**  -r     Sort in reverse order.
**  -u     Display only undefined symbols.
**  -U     Don't display undefined symbols.
**  -m     Display  the  N_SECT  type  symbols (Mach-O symbols) as (segment_name, section_name) followed by either external or non-external and then the symbol
**  						name.  Undefined, common, absolute and indirect symbols get displayed as (undefined), (common), (absolute), and (indirect), respectively.
**  -x     Display the symbol table entry's fields in hexadecimal, along with the name as a string.
**  -j     Just display the symbol names (no value or type).
**  -l     List a pseudo symbol .section_start if no symbol has as its value the starting address of the section.  (This is used with the -s option above.)
**  -f     For nm-classic(1) this displays the symbol table of a dynamic library flat (as one file not separate modules).  This is obsolete and  not  supported
**  			with llvm-nm(1).
**  -A     Write the pathname or library name of an object on each line.
**  -P     Write information in a portable output forma
*/

static t_options_map options_map[] = {
		{ "a", ALL_SYMBOL, NULL },
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
		{ "radix", RADIX, NULL },// true
		{ NULL, 0, NULL },
};


// static int handle_option_waiting_value(t_options *options, const char *name)
// {
// 	size_t j;

// 	j = 0;
// 	while (options_map[j].name != NULL)
// 	{
// 		if (!ft_strcmp(name + 2, options_map[j].name)) {
// 			((int*)options)[options_map[j].offset] = 1;

// 			return (EXIT_OK);
// 		}

// 		j++;
// 	}

// 	print_error_on_option("nm: unrecognized option ", name);

// 	return (EXIT_FAILURE);
// }

/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

int print_error_duplicated_option(const char *data)
{
    size_t len;
    char error_buffer[MAX_ERROR_BUFFER];

    memset(error_buffer, 0, sizeof(char) * MAX_ERROR_BUFFER);

	len = 0;

	// for the part
    memcpy(error_buffer + len, "nm: for the -", ft_strlen("nm: for the -") * sizeof(char));
    len += ft_strlen("nm: for the -");

	// option part
	if (data)
    {
    	memcpy(error_buffer + len,
			data,
			ft_strlen(data) * sizeof(char));
    	len += ft_strlen(data);
	}

	memcpy(error_buffer + len,
		" option: may only occur zero or one times!\n",
		ft_strlen(" option: may only occur zero or one times!\n") * sizeof(char));
    len += ft_strlen(" option: may only occur zero or one times!\n");

    write(2, error_buffer, len * sizeof(char));

    return (1);
}

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
				return (print_error_duplicated_option(options_map[j].name));
			
			if (!options_map[j].waiting_for_value)
				((int*)options)[options_map[j].offset] = 1;

			// Handle value option lika --arch x86_64
			else
				*last = &options_map[j];

			return (EXIT_OK);
		}

		j++;
	}

	print_error_on_option("nm: Unknown command line argument ", name);

	return (EXIT_FAILURE);
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
		ret = EXIT_OK;

		// Handle when the arg before was waiting for value
		if (last)
		{
			ret = last->waiting_for_value(options, av[i]);
			last = NULL;
		}
		
		// When the argument is '--', it means end arguments
		else if (is_a_end_arguments_string(av[i]))
		{
			options->end_index = i;
			return (ret);
		}
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
