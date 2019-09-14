#include "otool.h"

/*
** This map regroups all options :
**  -f print the fat headers
*/

static t_options_map options_map[] = {
		{ "f", PRINT_FAT_HEADER, NULL },
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

			return (-1);
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
