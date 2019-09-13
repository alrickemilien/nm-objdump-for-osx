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
		return (mach_o_error(-1, "%s: No such file or directory", path));
	}

 	if ((fstat(fd, &stats)) == -1)
	{
    	return (mach_o_error(-1, "%s: No such file or directory", path));
	}

	return (fd);
}
