#include "nm.h"

void print_error_on_option(const char *msg, const char *option)
{
	ft_putendl_fd(msg, 2);
	ft_putendl_fd(" : ", 2);
	ft_putendl_fd(option, 2);
}