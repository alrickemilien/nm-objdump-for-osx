#include "nm.h"

static int			exit_with_usage(int code)
{
	dprintf(2, "%s\n", USAGE);
	return (code);
}

int			main(int ac, char **av)
{
	int			i;
	int			exit_value;
	t_options	options;

	exit_value = EXIT_SUCCESS;
	i = 1;

	exit_value = read_options_arguments(ac, av, &options);

	if (options.help)
		return (exit_with_help(void));

	if (exit_value)
		return (exit_with_usage(exit_value));

	// Read every arg
	while (i < ac)
	{
		// Handle case when -- is set and do not handle as options all after --
		if (options.end_index != 0 &&  && nm(&options, av[i]) == EXIT_FAILURE)
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
