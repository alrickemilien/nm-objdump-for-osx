#include "mach_o.h"

int	load_archive_file(t_mach_o *file,
						void *archive_addr,
						uint64_t archive_size)
{
	file->archive_start_addr = archive_addr;
	file->archive_size = (uint64_t)archive_size;
	file->archive_member_header_addr = (void *)
		((uint8_t*)file->archive_start_addr + sizeof(STATIC_LIB_MAGIC) - 1);
	file->symdef_addr = NULL;
	file->members = NULL;
	file->ranlibs = NULL;
	file->ranlibs_64 = NULL;
	if (read_header_of_one_archives_member(file) == -1)
		return (-1);
	file->members = file->archive_member_header_addr;
	if (check_archive_addr_size(file,
		get_archive_member_starting_addr(file),
		(uint64_t)file->archive_member_header.st_size) == -1)
		return (-1);
	if (read_archive_symdef(file) == -1)
		return (-1);
	return (0);
}