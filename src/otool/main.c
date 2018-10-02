#include "otool.h"

/*
 *	nm
*/

int	is_directory(const char *path)
{
	int	fd;

	if ((fd = open(path, O_DIRECTORY)) != -1)
		return (1);
	return (0);
}

int	main(int ac, char ** av)
{
	int	i;
	int	fd;
	int	exit_value;

	exit_value = EXIT_SUCCESS;
	i = 1;
	while (i < ac)
	{
		if (is_directory(av[1])
		|| (fd = open(av[i], O_RDONLY)) < 0)
			exit_value = EXIT_FAILURE;
		i++;
	}
	return (exit_value);
}
