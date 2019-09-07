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

	if (read_options_arguments(ac, av, &options) == EXIT_FAILURE)
		return (exit_with_usage(EXIT_FAILURE));

	// Read every arg
	while (i < ac)
	{
		if (nm(&options, av[i]) == EXIT_FAILURE)
			exit_value = EXIT_FAILURE;
		i++;
	}

	// End
	return (exit_value);

}
