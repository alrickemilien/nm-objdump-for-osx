/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 14:42:16 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 14:42:17 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
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
		return (mach_o_error(0, NM_EACCESS, filename));
	else if (errno == EAGAIN)
		return (mach_o_error(0, NM_EAGAIN, filename));
	return (mach_o_error(0, NM_NO_SUCH_FILE, filename));
}

/*
** 1 - open the file in READ_ONLY mode
** 2 - Use fstat to get the file size
** 3 - Use mmap to load the file
*/

void		*map_loading_file(
	const char *filename, uint64_t *file_size)
{
	int			fd;
	void		*map;
	struct stat	st;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (INTADDR(custom_error(filename)));
	if ((fstat(fd, &st)) == -1 || st.st_size <= 0)
		return (INTADDR(mach_o_error(0, NM_ERR, filename)));
	*file_size = (off_t)st.st_size;
	if (S_ISDIR(st.st_mode))
		return (INTADDR(mach_o_error(0, "%s: Is a directory.\n", filename)));
	if ((st.st_mode & S_IFMT) != S_IFREG && (st.st_mode & S_IFMT) != S_IFLNK)
		return (INTADDR(mach_o_error(-1, NM_ERR, filename)));
	if (MAP_FAILED == (map = mmap(NULL, *file_size,
					PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
	{
		mach_o_error(-1, NM_ERR, filename);
		map = NULL;
	}
	close(fd);
	return (map);
}
