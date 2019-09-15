/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:36:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:59:03 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include <errno.h>

int			map_unloading_file(void *ptr, uint64_t file_size)
{
	if (munmap(ptr, file_size) == -1)
		return (-1);
	return (0);
}

static int	custom_error(const char *filename)
{
	if (errno == EACCES)
		return (mach_o_error(0, "'%s': Permission denied\n", filename));
	else if (errno == EAGAIN)
	{
		return (mach_o_error(0,
			"'%s': Resource temporarily unavailable\n", filename));
	}
	return (mach_o_error(0, "'%s': No such file or directory\n", filename));
}

/*
** 1 - open the file in READ_ONLY mode
** 2 - Use fstat to get the file size
** 3 - Use mmap to load the file
*/

void		*map_loading_file(const char *filename, uint64_t *file_size)
{
	int			fd;
	void		*map;
	struct stat	stats;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return ((void*)(intptr_t)custom_error(filename));
	if ((fstat(fd, &stats)) == -1 || stats.st_size <= 0)
		return (INTADDR(mach_o_error(0, OTOOL_DEFAULT_MACHO_ERROR, filename)));
	*file_size = (off_t)stats.st_size;
	if (S_ISDIR(stats.st_mode))
		return (INTADDR(mach_o_error(0, "'%s': Is a directory\n", filename)));
	if ((stats.st_mode & S_IFMT) != S_IFREG
		&& (stats.st_mode & S_IFMT) != S_IFLNK)
		return (INTADDR(mach_o_error(-1, OTOOL_DEFAULT_MACHO_ERROR, filename)));
	if (MAP_FAILED == (map = mmap(NULL, *file_size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
		mach_o_error(-1, OTOOL_DEFAULT_MACHO_ERROR, filename);
		map = NULL;
	}
	close(fd);
	return (map);
}
