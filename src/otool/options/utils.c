#include "nm.h"


static t_options_map g_waiting_value_options[] = {
		{ NULL, 0, NULL },
};

/*
** Return 1 when the argument name is an option like -l or -lR
** Return 0 when the argument name is an option like --reverse
*/

bool is_a_single_option(const char *name)
{
	if (name[0] == '-' && name[1] != '-')
		return (true);
	return (false);
}

/*
** Return 1 when the argument name is an option like --reverse
** Return 0 when the argument name is an option like -l or -lR
*/

bool is_a_multi_option(const char *name)
{
	if (name[0] == '-' && name[1] == '-' && name[2] != 0)
		return (true);
	return (false);
}

/*
** Return 1 when the argument name is --
** Return 0 othrwise
*/

bool is_a_end_arguments_string(const char *name)
{
	if (name[0] == '-' && name[1] == '-' && name[2] == 0)
		return (true);
	return (false);
}

/*
** Return 1 when the argument name is an option like --reverse
** Return 0 when the argument name is an option like -l or -lR
*/

bool is_an_option(const char *name)
{
	if (is_a_single_option(name)
        || is_a_end_arguments_string(name)
        || is_a_multi_option(name))
		return (true);
	return (false);
}

bool is_a_waiting_value_option(const char *name)
{
	size_t	j;
	size_t	len;
	size_t	off;

	off = 0;
	if (is_a_single_option(name))
		off = 1;
	if (is_a_multi_option(name))
		off = 2;
	j = 0;
	len = ft_strlen(name + off);
	while (g_waiting_value_options[j].name)
	{
		if (!ft_strcmp(name + off, g_waiting_value_options[j].name)
			&& len == ft_strlen(g_waiting_value_options[j].name))
			return (true);
		j++;
	}

	return (false);
}