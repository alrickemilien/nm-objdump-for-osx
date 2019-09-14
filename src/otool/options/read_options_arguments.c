#include "otool.h"

/*
** This map regroups all options :
**  -f print the fat headers
*/

static const t_options_map	g_options_map[] = {
	{ "f", PRINT_FAT_HEADER, NULL },
	{ NULL, 0, NULL },
};

/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

static int					handle_option(
	t_options *options,
	t_options_map **last,
	const char *name)
{
	size_t j;
	size_t len;

	len = ft_strlen(name);
	j = 0;
	while (g_options_map[j].name != NULL)
	{
		if (!ft_strcmp(name, g_options_map[j].name)
			&& len == ft_strlen(g_options_map[j].name))
		{
			if (((int*)options)[g_options_map[j].offset] == 1)
				return (mach_o_error(-1, 
					"for the -%s option: "
					"may only occur zero or one times!\n",
					g_options_map[j].name));
			if (!g_options_map[j].waiting_for_value)
				((int*)options)[g_options_map[j].offset] = 1;
			else
				*last = &g_options_map[j];
			return (0);
		}
		j++;
	}
	return (mach_o_error(-1,
		"Unknown command line argument '%s'\n", name));
}

/*
** Read args by filling t_options structure with 0 or 1
** list is the list of files passed as parameter
*/

int							read_options_arguments(
	int ac, char **av, t_options *options)
{
	int				i;
	int				ret;
	int				error;
	t_options_map	*last;

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
		else if (last)
		{
			ret = last->waiting_for_value(options, av[i]);
			last = NULL;
		}
		else if (is_a_end_arguments_string(av[i]))
			options->end_index = i;
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
