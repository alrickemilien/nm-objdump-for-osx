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

/*
** @return fd - file descriptor
*/
int load_file_descriptor(const char *path)
{
	int			     fd;
	struct stat  stats;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		mach_o_error(MACH_O_ERROR_MAP_LOADING);
		return (-1);
	}

  if ((fstat(fd, &stats)) == -1)
	{
    mach_o_error(MACH_O_ERROR_MAP_LOADING);
    return (-1);
  }

  return (fd);
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

	if (ac == 1)
	{
		ft_putendl("No input file.");
		return (0);
	}

	if (read_options_arguments(ac, av, &options) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	i = 1;
	while (i != ac && !is_an_option(av[i]))
	{
		build_mach_o_from_conf(&builder, av[i]);
		i++;
	}

	return (0);
}
