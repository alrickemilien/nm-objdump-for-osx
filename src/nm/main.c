#include "nm.h"

int			main(int ac, char **av)
{
	int			i;
	int			exit_code;
	t_options	options;

	i = 1;

	exit_code = read_options_arguments(ac, av, &options);

	if (options.HELP)
		return (exit_with_help());

	if (exit_code != 0)
		return (exit_code);

	exit_code = EXIT_SUCCESS;

	// Read every arg
	while (i < ac)
	{
		// Handle case when -- is set and do not handle as options all after --
		if (options.end_index != 0 && i != options.end_index)
		{
			if (i < options.end_index
				&& !is_an_option(av[i])
				&& nm(&options, av[i]) == EXIT_FAILURE)
				exit_code = EXIT_FAILURE;
			else if (i >= options.end_index && nm(&options, av[i]) == EXIT_FAILURE)
				exit_code = EXIT_FAILURE;
		}
		// Regular case without --
		else if (options.end_index == 0
			&& !is_an_option(av[i])
			&& nm(&options, av[i]) == EXIT_FAILURE)
			exit_code = EXIT_FAILURE;
		i++;
	}

	// End
	return (exit_code);
}
