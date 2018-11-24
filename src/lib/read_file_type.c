/*
** This file provides functions that read the file type
** (archive, fat arch, macho file)
** WARNING
** Do not mix file type (archive, fat arch, macho file)
** and macho file type (MH_OBJECT, MH_EXECUTE, MH_FVMLIB)
** specific for macho file header
*/

typedef uint32_t	t_file_type;

typedef struct s_map_file_type_checkers {
	typedef bool	(*t_f_is_ofile_type)(t_ofile *ofile);
	t_file_type		file_type;
}				t_map_file_type_checkers;


static bool		is_archive(t_ofile *ofile)
{
	if (ofile->file_size <= sizeof(STATIC_LIB_MAGIC))
		return (false);
	if (!memcmp(ofile->object_addr,
				STATIC_LIB_MAGIC,
				sizeof(STATIC_LIB_MAGIC) - 1))
		return (true);
	return (false);
}

static bool		is_fat(t_ofile *ofile)
{
	struct fat_header	*hdr;

	hdr = ofile->object_addr;
	if (ofile->file_size <= sizeof(hdr->magic))
		return (false);
	return (hdr->magic == FAT_MAGIC || hdr->magic == FAT_CIGAM
			|| hdr->magic == FAT_MAGIC_64 || hdr->magic == FAT_CIGAM_64);
}

static bool		is_macho(t_ofile *ofile)
{
	struct mach_header		*hdr;
	struct mach_header_64	*hdr_64;

	hdr = ofile->object_addr;
	hdr_64 = ofile->object_addr;
	if (ofile->file_size <= sizeof(hdr->magic)
		|| ofile->file_size <= sizeof(hdr_64->magic))
		return (false);
	return (hdr->magic == MH_MAGIC || hdr->magic == MH_CIGAM ||
			hdr_64->magic == MH_MAGIC_64 || hdr_64->magic == MH_CIGAM_64);
}

static bool		is_unknown(t_ofile *ofile)
{
	(void)ofile;
	return (true);
}

static const t_map_file_type_checkers		g_types_map[SUPPORTED_OFILE_TYPES] = {
	{&is_archive, OFILE_ARCHIVE},
	{&is_fat, OFILE_FAT},
	{&is_macho, OFILE_MACHO},
	{&is_unknown, OFILE_UNKNOWN},
};

t_file_type	read_file_type(t_ofile *ofile)
{
	uint32_t						i;

	i = 0;
	while (i < SUPPORTED_OFILE_TYPES)
	{
		if (g_types_map[i].checker(ofile))
			return (g_types_map[i].file_type);
		i++;
	}
	return (OFILE_UNKNOWN);
}