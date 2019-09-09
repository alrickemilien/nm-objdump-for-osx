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
		{ "a", ALL_SYMBOL, false },
		{ "g", ONLY_GLOBAL_SYMBOL, false },
		{ "n", SORT_NUMERIC, false },
		{ "o", PREPEND_FILE_ARCHIVE_NAME, false },
		{ "p", DO_NOT_SORT, false },
		{ "r", REVERSE_SORT, false },
		{ "u", ONLY_UNDEFINED_SYMBOL, false },
		{ "U", DO_NOT_DISPLAY_UNDEFINED_SYMBOL, false },
		{ "m", DISPLAY_NSECT, false },
		{ "x", DISPLAY_HEXA, false },
		{ "j", ONLY_SYMBOL_NAME, false },
		{ "l", LIST_PSEUDO_SYMBOL, false },
		{ "f", DISPLAY_DYNAMIC_LIB_SYMBOL, false },
		{ "A", DISPLAY_PATH_NAME, false },
		{ "P", DISPLAY_PORTABLE, false },
		{ "t", RADIX, true },
		{ "p", DO_NOT_SORT, false },
		{ "D", ONLY_DYNAMIC, false },
		{ "arch" ARCH_TYPE, true, },
		{ "s" SEGMENT_SECTION, true, },
		{ "print-size" PRINT_SIZE, false },
		{ "dynamic", ONLY_DYNAMIC, false },
		{ "size-sort", SORT_SIZE, false },
		{ "print-file-name" PREPEND_FILE_ARCHIVE_NAME, false },
		{ "undefined-only", ONLY_UNDEFINED_SYMBOL, false, },
		{ "no-sort" DO_NOT_SORT, false },
		{ "reverse-sort" REVERSE_SORT, false },
		{ "print-after-all" PRINT_AFTER_ALL, false },
		{ "print-before-all" PRINT_BEFORE_ALL, false },
		{ "just-symbol-name" ONLY_SYMBOL_NAME, false },
		{ "extern-only" ONLY_GLOBAL_SYMBOL, false },
		{ "defined-only" DEFINED_ONLY, false },
		{ "synthetic" DEFINED_ONLY, false },
		{ "radix", RADIX, true },
		{ NULL, 0, false },
};

/*
** Read each option of multi_options like -l or -la
** Starts at 1 the index i to skip the - from -la for example
** Check if options_map[j].name[1] == 0 means that we want only a letter string
** to  avoid comparing -r and --recursive first letter, which are two different options
*/

static int handle_multi_option(t_options *options, const char *name)
{
	size_t i;
	size_t j;

	i = 1;
	while (name[i])
	{
		j = 0;
		while (j < OPTIONS_MAP_LENGTH) {
			if (options_map[j].name[1] == 0 && name[i] == options_map[j].name[0])
			{
				((int*)options)[options_map[j].offset] = 1;
				break;
			}

			j++;
		}

		if (j == OPTIONS_MAP_LENGTH) {
			print_error_on_option("nm: invalid option -- ", name);
			return (EXIT_FAILURE);
		}

		i++;
	}

	return (EXIT_OK);
}

/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

static int handle_single_option(t_options *options, const char *name)
{
	size_t j;

	j = 0;
	while (options_map[j].name != NULL)
	{
		if (!ft_strcmp(name + 2, options_map[j].name)) {
			((int*)options)[options_map[j].offset] = 1;

			return (EXIT_OK);
		}

		j++;
	}

	print_error_on_option("nm: unrecognized option ", name);

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

	ft_memset(options, 0, sizeof(t_options));

	i = 1;
	while (i < ac)
	{
		ret = EXIT_OK;

		// When the argument is '--', it means end arguments
		if (is_a_end_arguments_string(av[i]))
		{
			options->end_options_index = i;
			return (ret);
		}
		else if (is_a_single_option(av[i])) {
			ret = handle_single_option(options, av[i]);
		} else if (is_a_multi_option(av[i])) {
			ret = handle_multi_option(options, av[i]);
		}

		i++;
	}

	return (EXIT_OK);
}
