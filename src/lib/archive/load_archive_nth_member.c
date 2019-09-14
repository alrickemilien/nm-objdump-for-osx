#include "mach_o.h"

static void	*find_archive_member(t_mach_o *file, uint64_t n_member)
{
	size_t	i;

	LOGDEBUG("------- find_archive_member\n");

	file->archive_member_header_addr = file->members;
	i = 0;
	while (i < n_member + 1)
	{
		LOGDEBUG("------- find_archive_member iter number %ld\n", i);
		if (read_header_of_one_archives_member(file) == -1)
		{
			LOGDEBUG("i: %ld - %s\n", i, " JE RETURN NUL YAAAAAAA");
			return (NULL);
		}
		file->archive_member_header_addr = (void *)((uint8_t *)
									file->archive_member_header_addr
									+ 60
									+ (file->archive_member_header.st_size));
		i++;
	}
	return (file->archive_member_header_addr);
}

int				load_archive_nth_member(t_mach_o *file,
											uint64_t n_member,
											bool *error)
{
	LOGDEBUG("------ load_archive_nth_member\n");
	LOGDEBUG("INFO file->nmembers : %lld\n", file->nmembers);
    if (!file->symdef_addr || (!file->ranlibs && !file->ranlibs_64))
        return (-1);
	if (n_member >= file->nmembers && error)
		*error = 1;
	file->archive_member_header_addr = NULL;
	ft_memset(&file->archive_member_header, 0, sizeof(t_member_header));
	file->archive_member_header_addr = find_archive_member(file, n_member);
	LOGDEBUG("INFO file->archive_member_header_addr : %p at n_member %lld\n", 
		file->archive_member_header_addr,
		n_member);
	if (read_header_of_one_archives_member(file) == -1
		|| !(file->archive_member_header.st_size > 0))
	{
		LOGDEBUG("read_header_of_one_archives_member(file) : %d\n",
			read_header_of_one_archives_member(file));
		LOGDEBUG("file->archive_member_header.st_size > 0 : %d\n",
			file->archive_member_header.st_size > 0);
		return (-1);
	}
	LOGDEBUG("INFO file->archive_member_header.st_size : %lld\n"
		"INFO archive_member_starting_addr : %p\n", file->archive_member_header.st_size,
		get_archive_member_starting_addr(file));
	return (load_macho_file(file,
                            file->path,
							get_archive_member_starting_addr(file),
							(uint64_t)file->archive_member_header.st_size));
}
