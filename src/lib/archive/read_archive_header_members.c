#include "mach_o_utils.h"

int32_t					read_archive_header_members(t_macho *ofile)
{
	// The adrress of the header of a member of the archive
	uint8_t			*member_header_addr;

	member_header_addr = (uint8_t *)ofile->archive_member_header_addr;
	
	if (-1 == check_archive_addr_size(ofile, member_header_addr, 60))
		return (-1);
	
	if (-1 == read_archive_member_name(ofile))
		return (-1);
	
	ofile->archive_member_header.st_time = (uint8_t*)(member_header_addr + 16);
	
	ofile->archive_member_header.st_uid = ft_atou((const char *)member_header_addr
												+ 28);
	
	ofile->archive_member_header.st_gid = ft_atou((const char *)member_header_addr
												+ 34);
	
	ofile->archive_member_header.st_mode = ft_atohu_base(
		(const char *)member_header_addr + 40, "01234567");
	
	ofile->archive_member_header.st_size = ft_atoll(
		(const char *)member_header_addr + 48);
	
	if (ofile->archive_member_header.st_size < 0)
	{
		ft_dprintf(2, "Invalid st_size in archive member\n");
		return (-1);
	}
	
	return (0);
}