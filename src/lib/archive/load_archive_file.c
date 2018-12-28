#include "mach_o_utils.h"

int32_t	load_archive_file(t_macho *ofile,
						void *archive_addr,
						size_t archive_size)
{
	ofile->archive_start_addr = archive_addr;

	ofile->archive_size = (uint64_t)archive_size;

	// Set a cursor on the first archive member header
	ofile->archive_member_header_addr = (void *)
		((uint8_t*)ofile->archive_start_addr + sizeof(STATIC_LIB_MAGIC) - 1);

	ofile->symdef_addr = NULL;
	ofile->members = NULL;
	ofile->ranlibs = NULL;
	ofile->ranlibs_64 = NULL;

	if (-1 == read_archive_header_members(ofile))
		return (-1);

	ofile->members = ofile->archive_member_header_addr;

	if (-1 == check_archive_addr_size(ofile,
		get_archive_member_starting_addr(ofile),
		(uint64_t)ofile->archive_member_header.st_size))
		return (-1);

	if (-1 == read_archive_symdef(ofile))
		return (-1);

	return (0);
}