#include "nm.h"

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
	if (name[0] == '-' && name[1] == '-')
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