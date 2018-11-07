#include "mach_o_builder.h"

/*
** 1 - Load the file config
*/

void print_error_on_option(const char *msg, const char *option)
{
	ft_putendl_fd(msg, 2);
	ft_putendl_fd(" : ", 2);
	ft_putendl_fd(option, 2);
}

void del(void *v, size_t size)
{
	(void)size;
	free(v);
}

static inline bool is_an_option(const char *s)
{
	if (s[0] == '-')
		return (true);
	return (false);
}

int main(int ac, const char **av)
{
	int								i;
	t_options					options;
	t_mach_o_builder	builder;
	void 							*buffer;
	size_t 						size;
	int  							ret;

	if (ac == 1)
	{
		ft_putendl("No input file.");
		return (0);
	}

	if (read_options_arguments(ac, av, &options) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	i = 1;
	while (i != ac && !is_an_option(av[i]))
		build_mach_o_from_conf(&builder, av[i++]);

	ret = mach_o_builder(&builder, &buffer, &size);

	write(1, buffer, size);

	if (NULL != buffer)
		free(buffer);

	ft_lstdel(&builder.cmd_list, &del);

	return (0);
}
