int32_t	read_archive_member_name(t_macho *ofile)
{
	if (!memcmp(ofile->archive_member_header_addr, 
				LONG_ARCHIVE_NAME_MAGIC,
				sizeof(LONG_ARCHIVE_NAME_MAGIC) - 1))
	{
		ofile->archive_member_header.name_length = ft_atou(
			(char *)ofile->archive_member_header_addr
			+ sizeof(LONG_ARCHIVE_NAME_MAGIC) - 1);
		
		if (ofile->archive_member_header.name_length < 0)
		{
			ft_dprintf(2, "Invalid member_name size\n");
			return (-1);
		}
		
		ofile->archive_member_header.member_name =
			(uint8_t*)ofile->archive_member_header_addr + 60;
		
		ofile->archive_member_header.long_name = true;
	}
	else
	{
		ofile->archive_member_header.member_name =
			(uint8_t*)ofile->archive_member_header_addr;
		
		ofile->archive_member_header.name_length = 16;
		
		ofile->archive_member_header.long_name = false;
	}
	
	return (0);
}