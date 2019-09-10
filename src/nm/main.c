#include "nm.h"

int			main(int ac, char **av)
{
	int			i;
	int			exit_value;
	t_options	options;

	i = 1;

	exit_value = read_options_arguments(ac, av, &options);

	if (options.HELP)
		return (exit_with_help());

	if (exit_value != 0)
		return (exit_value);

	exit_value = EXIT_SUCCESS;
	// Read every arg
	while (i < ac)
	{
		// Handle case when -- is set and do not handle as options all after --
		if (options.end_index != 0)
		{
			if (i < options.end_index && !is_an_option(av[i]) && nm(&options, av[i]) == EXIT_FAILURE)
				exit_value = EXIT_FAILURE;
			else if (i >= options.end_index && nm(&options, av[i]) == EXIT_FAILURE)
				exit_value = EXIT_FAILURE;
		}
		// Regular case without --
		else if (options.end_index == 0 && !is_an_option(av[i]) && nm(&options, av[i]) == EXIT_FAILURE)
			exit_value = EXIT_FAILURE;
		i++;
	}

	// End
	return (exit_value);

}
