#include "mach_o.h"

int32_t					read_header_of_one_archives_member(t_mach_o *file)
{
	// The adrress of the header of a member of the archive
	uint8_t			*member_header_addr;

	LOGDEBUG("---- read_header_of_one_archives_member\n");

	member_header_addr = (uint8_t *)file->archive_member_header_addr;

	if (check_archive_addr_size(file, member_header_addr, 60) == -1)
	{
		LOGDEBUG("JI UN BLEM LALLALA\n");
		return (-1);
	}
	
	if (read_archive_member_name(file) == -1)
	{
		LOGDEBUG("JI UN BLEM ICI\n");
		return (-1);
	}
	
	file->archive_member_header.st_time = (uint8_t*)(member_header_addr + 16);
	
	file->archive_member_header.st_uid = ato16u((const char *)member_header_addr
												+ 28);
	
	file->archive_member_header.st_gid = ato16u((const char *)member_header_addr
												+ 34);
	
	file->archive_member_header.st_mode = ato16u_base(
		(const char *)member_header_addr + 40, "01234567");
	
	file->archive_member_header.st_size = ato64(
		(const char *)member_header_addr + 48);
	
	if (file->archive_member_header.st_size < 0)
	{
		dprintf(2, "Invalid st_size in archive member\n");
		return (-1);
	}
	
	return (0);
}