#include "mach_o.h"

int32_t	load_archive_file(t_mach_o *file,
						void *archive_addr,
						uint64_t archive_size)
{
	file->archive_start_addr = archive_addr;

	LOGDEBUG("A1\n");

	file->archive_size = (uint64_t)archive_size;

	// Set a cursor on the first archive member header
	file->archive_member_header_addr = (void *)
		((uint8_t*)file->archive_start_addr + sizeof(STATIC_LIB_MAGIC) - 1);

	LOGDEBUG("A2\n");

	file->symdef_addr = NULL;
	file->members = NULL;
	file->ranlibs = NULL;
	file->ranlibs_64 = NULL;

	// read archive info
	if (read_header_of_one_archives_member(file) == -1)
		return (-1);

	LOGDEBUG("A3\n");

	file->members = file->archive_member_header_addr;
	LOGDEBUG("INFO file->members adresse : %p\n", file->members);
	LOGDEBUG("INFO file->archive_member_header_addr : %p\n", file->archive_member_header_addr);

	if (check_archive_addr_size(file,
		get_archive_member_starting_addr(file),
		(uint64_t)file->archive_member_header.st_size) == -1)
		return (-1);

	LOGDEBUG("A4\n");

	if (read_archive_symdef(file) == -1)
		return (-1);

	LOGDEBUG("A5\n");

	return (0);
}