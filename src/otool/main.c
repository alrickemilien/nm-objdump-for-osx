#include "otool.h"

/*
**	otool
*/

int	main(int ac, char **av)
{
	int	i;
	int	exit_value;

	(void)av;

	exit_value = EXIT_SUCCESS;
	i = 1;
	while (i < ac)
	{
		i++;
	}
	return (exit_value);
}


// #include "otool.h"

// int			main(int ac, char **av)
// {
// 	int			i;
// 	int			exit_code;
// 	t_options	options;
// 	int 		last;

// 	i = 1;

// 	exit_code = read_options_arguments(ac, av, &options);

// 	if (options.file_count == 0)
// 		return (exit_with_help());

// 	if (exit_code != 0)
// 		return (exit_code);

// 	exit_code = 0;
// 	last = 0;
// 	// Read every arg
// 	while (i < ac)
// 	{
// 		// Handle case when -- is set and do not handle as options all after --
// 		if (options.end_index != 0)
// 		{
// 			// Handle --arch x86_64
// 			if (i <= options.end_index && !last && is_a_waiting_value_option(av[i]))
// 				last = 1;
// 			// Handle x86_64 part of --arch x86_64
// 			else if (i < options.end_index && last)
// 				last = 0;
// 			else if (i < options.end_index
// 				&& !is_an_option(av[i])
// 				&& otool(&options, av[i]) < 0)
// 				exit_code = 1;
// 			else if (i > options.end_index && otool(&options, av[i]) < 0)
// 				exit_code = 1;
// 		}
// 		// Regular case without --
// 		else
// 		{
// 			// Handle --arch x86_64
// 			if (!last && is_a_waiting_value_option(av[i]))
// 				last = 1;
// 			// Handle x86_64 part of --arch x86_64
// 			else if (last)
// 				last = 0;
// 			else if (!is_an_option(av[i]) && otool(&options, av[i]) < 0)
// 				exit_code = 1;
// 		}

// 		i++;
// 	}

// 	// End
// 	return (exit_code);
// }
