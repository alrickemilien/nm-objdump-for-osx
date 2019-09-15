/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options_arguments.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:04:59 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:05:00 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			{
				return (mach_o_error(-1, OTOOL_MULTI_OPT_ERROR,
					g_options_map[j].name));
			}
			if (!g_options_map[j].waiting_for_value)
				((int*)options)[g_options_map[j].offset] = 1;
			else
				ft_memcpy(last, &g_options_map[j], sizeof(t_options_map*));
			return (0);
		}
		j++;
	}
	return (mach_o_error(-1,
		"Unknown command line argument '%s'\n", name));
}

void						read_one_options_argument(
	char *arg,
	t_options *options,
	int i,
	int *error)
{
	int						ret;
	static t_options_map	*last = NULL;

	ret = 0;
	if (options->end_index)
		options->file_count += 1;
	else if (last)
	{
		ret = last->waiting_for_value(options, arg);
		last = NULL;
	}
	else if (is_a_end_arguments_string(arg))
		options->end_index = i;
	else if (is_a_single_option(arg))
		ret = handle_option(options, &last, arg + 1);
	else if (is_a_multi_option(arg))
		ret = handle_option(options, &last, arg + 2);
	else
		options->file_count += 1;
	if (ret != 0)
		*error = ret;
}

/*
** Read args by filling t_options structure with 0 or 1
** list is the list of files passed as parameter
*/

int							read_options_arguments(
	int ac, char **av, t_options *options)
{
	int				i;
	int				error;

	ft_memset(options, 0, sizeof(t_options));
	error = 0;
	options->file_count = 0;
	i = 1;
	while (i < ac)
	{
		read_one_options_argument(av[i], options, i, &error);
		i++;
	}
	return (error);
}
