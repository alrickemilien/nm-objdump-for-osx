#include "mach_o_builder.h"

/*
** @return fd - file descriptor
*/
int load_file_descriptor(const char *path)
{
	int			     fd;
	struct stat  stats;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		mach_o_error(MACH_O_ERROR_MAP_LOADING, NULL);
		return (-1);
	}

  if ((fstat(fd, &stats)) == -1)
	{
    mach_o_error(MACH_O_ERROR_MAP_LOADING, NULL);
    return (-1);
  }

  return (fd);
}
