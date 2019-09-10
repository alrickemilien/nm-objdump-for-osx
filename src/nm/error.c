#include "nm.h"

void print_error_on_option(const char *msg, const char *option)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(option, 2);
	ft_putendl_fd("'.", 2);
}