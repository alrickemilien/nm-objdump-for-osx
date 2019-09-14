#include "otool.h"

static void loop_over_command_line(
		char *opt,
		t_options *options,
		int *exit_code, int *last)
{
	if (options->end_index != 0)
	{
		if (i <= options->end_index
			&& !(*last)
			&& is_a_waiting_value_option(opt))
			*last = 1;
		else if (i < options->end_index && last)
			*last = 0;
		else if (i < options->end_index
			&& !is_an_option(opt)
			&& otool(&options, opt) < 0)
			exit_code = 1;
		else if (i > options->end_index
			&& otool(&options, opt) < 0)
			exit_code = 1;
	}
	else
	{
		if (!last && is_a_waiting_value_option(opt))
			*last = 1;
		else if (last)
			*last = 0;
		else if (!is_an_option(opt)
			&& otool(&options, opt) < 0)
			exit_code = 1;
	}
}

int			main(int ac, char **av)
{
	int			i;
	int			exit_code;
	int 		last;
	t_options	options;

	exit_code = 0;
	init_prefix_error(av[0]);
	exit_code = read_options_arguments(ac, av, &options);
	if (options.file_count == 0)
		return (exit_with_help());
	if (exit_code != 0)
		return (exit_code);
	i = 1;
	last = 0;
	while (i < ac)
		loop_over_command_line(av[i++], options, &exit_code, &last);
	return (exit_code);
}
