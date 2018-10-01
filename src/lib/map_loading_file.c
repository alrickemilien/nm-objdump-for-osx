#include "mach_o_utils.h"

static print_error(char *filename, char *str)
{
  ft_putstr_fd(2, filename);
  ft_putstr_fd(2, ": ");
  ft_putendl_fd(2, str);
}

/*
** 1 - open the file in READ_ONLY mode
** 2 - Use fstat to get the file size
** 3 - Use mmap to load the file
*/
void	*map_loading_file(char *filename, uint64_t *file_size)
{
	int			fd;
	void		*map;
	struct stat	stats;

	if (fd = open(filename, O_RDONLY) == -1))
	{
		print_error(filename, "File does not exist or permission denied");
		return (NULL);
	}

  if ((fstat(fd, &stats)) == -1)
		return (NULL);

  if (stats.st_size <= 0)
		return (NULL);

  *file_size = ((uint64_t)stats.st_size);

  if (MAP_FAILED == (map = mmap(NULL, *file_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
    print_error(filename, "File does not exist or permission denied");
		map = NULL;
	}

  close(fd);

  return (map);
}
