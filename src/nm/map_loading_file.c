#include "nm.h"
#include <errno.h>

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

void	*map_loading_file(const char *filename, uint64_t *file_size)
{
	int			     fd;
	void		     *map;
	struct stat  stats;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
    if (errno == EACCES)
		  mach_o_error(0, "%s: Permission denied.\n", filename);
    else if (errno == EAGAIN)
		  mach_o_error(0, "%s: Resource temporarily unavailable.\n", filename);
    else
		  mach_o_error(0, "%s: No such file or directory.\n", filename);
		return (NULL);
	}

  if ((fstat(fd, &stats)) == -1)
    return ((void*)(intptr_t)mach_o_error(0, NM_DEFAULT_MACHO_ERROR, filename));

  if (stats.st_size <= 0)
    return ((void*)(intptr_t)mach_o_error(0, NM_DEFAULT_MACHO_ERROR, filename));

  *file_size = (off_t)stats.st_size;

  if (S_ISDIR(stats.st_mode))
    return ((void*)(intptr_t)mach_o_error(0, "%s: Is a directory.\n", filename));

  if ((stats.st_mode & S_IFMT) != S_IFREG && (stats.st_mode & S_IFMT) != S_IFLNK)
    return ((void*)(intptr_t)mach_o_error(-1, NM_DEFAULT_MACHO_ERROR, filename));

  if (MAP_FAILED == (map = mmap(NULL, *file_size,
				PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
    mach_o_error(-1, NM_DEFAULT_MACHO_ERROR, filename);
		map = NULL;
	}

  close(fd);

  return (map);
}
