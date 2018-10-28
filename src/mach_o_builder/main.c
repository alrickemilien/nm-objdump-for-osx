#include "mach_o_builder.h"

/*
** 1 - Load the file config
*/

/*
** @return fd - file descriptor
*/
static int load_file_descriptor(const char *path)
{
	int			     fd;
	struct stat  stats;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		mach_o_error(MACH_O_ERROR_MAP_LOADING);
		return (-1);
	}

  if ((fstat(fd, &stats)) == -1) {
    mach_o_error(MACH_O_ERROR_MAP_LOADING);
    return (-1);
  }

  return (fd);
}

int build_mach_o_from_conf(const char *path)
{
	int		fd;
	char	*line;

	fd = load_file_descriptor(path);

	if (fd == -1)
		return (EXIT_FAILURE)

	while(get_next_line(fd, &line))
	{
		;
	}

	return (0);
}

int main(int ac, const char **av)
{
	int	i;

	if (ac == 1)
	{
		ft_putendl("No input file.");

		return (0);
	}

	i = 1;
	while (i != ac)
	{
		build_mach_o_from_conf(av[i]);
		i++;
	}
	
	return (0);
}