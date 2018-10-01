#include "nm_otool.h"

/*
** This map regroups all options
*/

static t_options_map options_map[OPTIONS_MAP_LENGTH] = {
		{
			"foo",
			FOO_OPTION,
		},
};

/*
** Return 1 when the argument name is an option like -l or -lR
** Return 0 when the argument name is an option like --reverse
*/

static inline bool is_a_multi_option(const char *name) {
	if (name[0] == '-' && name[1] != '-')
		return (1);

	return (0);
}

/*
** Return 1 when the argument name is an option like --reverse
** Return 0 when the argument name is an option like -l or -lR
*/

static inline bool is_a_single_option(const char *name) {
	if (name[0] == '-' && name[1] == '-')
		return (1);

	return (0);
}

/*
** Read each option of multi_options like -l or -la
** Starts at 1 the index i to skip the - from -la for example
** Check if options_map[j].name[1] == 0 means that we want only a letter string
** to  avoid comparing -r and --recursive first letter, which are two different options
*/

static int handle_multi_option(t_options *options, const char *name) {
	int i;
	int j;

	i = 1;
	while (name[i])
	{
		j = 0;
		while (j < OPTIONS_MAP_LENGTH) {
			if (options_map[j].name[1] == 0 && name[i] == options_map[j].name[0]) {
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

static int handle_single_option(t_options *options, const char *name) {
	int j;

	j = 0;
	while (j < OPTIONS_MAP_LENGTH)
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

int read_options_arguments(int ac, char **av, t_options *options) {
	int						i;
	int						ret;

	ft_bzero(options, sizeof(t_options));

	i = 1;
	while (i < ac)
	{
		ret = EXIT_OK;

		if (is_a_single_option(av[i])) {
			ret = handle_single_option(options, av[i]);
		} else if (is_a_multi_option(av[i])) {
			ret = handle_multi_option(options, av[i]);
		}

		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);

		i++;
	}


	return (EXIT_OK);
}
