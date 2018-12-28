static inline bool	is_symdef_32(const t_macho *ofile)
{
	return (ft_strncmp((const char *)ofile->archive_member_header.member_name,
				SYMDEF,
				sizeof(SYMDEF))
		|| ft_strncmp((const char *)ofile->archive_member_header.member_name,
				SYMDEF_SORTED,
				sizeof(SYMDEF_SORTED)));
}

static inline bool	is_symdef_64(const t_macho *ofile)
{
	return (
		ft_strncmp((const char *)ofile->archive_member_header.member_name,
			SYMDEF_64,
			sizeof(SYMDEF_64))
		|| ft_strncmp((const char *)ofile->archive_member_header.member_name,
			SYMDEF_64_SORTED,
			sizeof(SYMDEF_64_SORTED)));
}

static inline void	read_archive_symdef_32(t_macho *ofile)
{
	ofile->ranlibs = get_archive_member_starting_addr(ofile);

	ofile->nran = *(uint32_t*)(void *)ofile->ranlibs / sizeof(struct ranlib);
	
	ofile->ranlibs = (void *)((uint8_t*)ofile->ranlibs + 4);
	
	ofile->string_table_size = (uint64_t)*(uint32_t *)(void *)(
		(uint8_t *)ofile->ranlibs + ofile->nran * sizeof(struct ranlib));
	
	ofile->string_table = (char *)((uint8_t *)ofile->ranlibs
					+ ofile->nran * sizeof(struct ranlib) + sizeof(uint32_t));
	
	ofile->nmembers = read_archive_nmembers(ofile);
}

static inline void	read_archive_symdef_64(t_macho *ofile)
{
	ofile->ranlibs_64 = get_archive_member_starting_addr(ofile);
	
	ofile->nran = *(uint64_t*)(void *)ofile->ranlibs_64
									/ sizeof(struct ranlib_64);
	ofile->ranlibs_64 = (void *)((uint8_t*)ofile->ranlibs + 8);
	
	ofile->string_table_size = *(uint64_t *)(void *)(
		(uint8_t *)ofile->ranlibs_64 + ofile->nran * sizeof(struct ranlib_64));
	
	ofile->string_table = (char *)((uint8_t *)ofile->ranlibs_64
				+ ofile->nran * sizeof(struct ranlib_64) + sizeof(uint64_t));
	
	ofile->nmembers = read_archive_nmembers(ofile);
}

int32_t				read_archive_symdef(t_macho *ofile)
{
	ofile->symdef_addr = ofile->archive_member_header_addr;
	if (is_symdef_32(ofile))
	{
		read_archive_symdef_32(ofile);
	}
	else if (is_symdef_64(ofile))
	{
		read_archive_symdef_64(ofile);
	}
	else
	{
		mach_o_error(MACH_O_ERROR_INVALID_SYMDEF);
		return (-1);
	}
	
	return (0);
}