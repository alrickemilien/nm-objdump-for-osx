#include "mach_o_utils.h"

static void print_error(char *filename, char *str)
{
  ft_putstr_fd(filename, 2);
  ft_putstr_fd(": ", 2);
  ft_putendl_fd(str, 2);
}

int		map_unloading_file(void *ptr, uint64_t file_size)
{
	if (munmap(ptr, file_size) == -1)
		return (-1);
	return (0);
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

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		print_error(filename, "File does not exist or permission denied");
		return (NULL);
	}

  if ((fstat(fd, &stats)) == -1)
		return (NULL);

  if (stats.st_size <= 0)
		return (NULL);

  *file_size = ((uint64_t)stats.st_size);

  if (stats.st_mode != S_IFREG && stats.st_mode != S_IFLNK)
	return (0);

  if (MAP_FAILED == (map = mmap(NULL, *file_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
    print_error(filename, "File does not exist or permission denied");
		map = NULL;
	}

  close(fd);

  return (map);
}
