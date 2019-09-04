#include "mach_o.h"

int32_t	read_archive_member_name(t_mach_o *file)
{
	if (!memcmp(file->archive_member_header_addr, 
				LONG_ARCHIVE_NAME_MAGIC,
				sizeof(LONG_ARCHIVE_NAME_MAGIC) - 1))
	{
		file->archive_member_header.name_length = ato16u(
			(char *)file->archive_member_header_addr
			+ sizeof(LONG_ARCHIVE_NAME_MAGIC) - 1);
		
		if (file->archive_member_header.name_length < 0)
		{
			dprintf(2, "Invalid member_name size\n");
			return (-1);
		}
		
		file->archive_member_header.member_name =
			(uint8_t*)file->archive_member_header_addr + 60;
		
		file->archive_member_header.long_name = true;
	}
	else
	{
		file->archive_member_header.member_name =
			(uint8_t*)file->archive_member_header_addr;
		
		file->archive_member_header.name_length = 16;
		
		file->archive_member_header.long_name = false;
	}
	
	return (0);
}