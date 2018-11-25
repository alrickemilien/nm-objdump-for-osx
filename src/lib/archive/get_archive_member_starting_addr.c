#include "mach_o_utils.h"

void		*get_archive_member_starting_addr(t_macho *ofile)
{
	uint8_t		*addr;

	if (!ofile->archive_start_addr || !ofile->archive_member_header_addr)
		return (NULL);

	addr = (uint8_t *)(ofile->archive_member_header_addr + 60);

	if (ofile->archive_member_header.long_name) {
		addr += (uint64_t)ofile->archive_member_header.name_length | 0x4;
	}

	return ((uint8_t *)addr);
}