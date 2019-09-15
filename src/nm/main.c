/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:16:30 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:16:57 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int				main(int ac, char **av)
{
	int			i;
	int			exit_code;
	t_options	options;
	int 		last;

	i = 1;
	init_prefix_error(av[0]);
	exit_code = read_options_arguments(ac, av, &options);
	if (options.HELP)
		return (exit_with_help());
	if (exit_code != 0)
		return (exit_code);
	if (options.file_count == 0)
		return (nm(&options, "a.out") < 0 ? 1 : 0);
	exit_code = 0;
	last = 0;
	while (i < ac)
	{
		if (options.end_index != 0)
		{
			if (i <= options.end_index && !last && is_a_waiting_value_option(av[i]))
				last = 1;
			else if (i < options.end_index && last)
				last = 0;
			else if (i < options.end_index
					&& !is_an_option(av[i])
					&& nm(&options, av[i]) < 0)
				exit_code = 1;
			else if (i > options.end_index && nm(&options, av[i]) < 0)
				exit_code = 1;
		}
		else
		{
			if (!last && is_a_waiting_value_option(av[i]))
				last = 1;
			else if (last)
				last = 0;
			else if (!is_an_option(av[i]) && nm(&options, av[i]) < 0)
				exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
