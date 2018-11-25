#include "mach_o_utils.h"

/*
** This file provides functions that read the file type
** (archive, fat arch, macho file)
** WARNING
** Do not mix file type (archive, fat arch, macho file)
** and macho file type (MH_OBJECT, MH_EXECUTE, MH_FVMLIB)
** specific for macho file header
*/

typedef struct s_map_file_type_checkers {
	bool			(*checker)(t_mach_o *ofile);
	t_file_type		file_type;
}				t_map_file_type_checkers;


static bool		is_archive_file(t_mach_o *ofile)
{
	if (ofile->file_size <= sizeof(STATIC_LIB_MAGIC)) {
		return (false);
	}
	
	if (!memcmp(
			ofile->addr,
			STATIC_LIB_MAGIC,
			sizeof(STATIC_LIB_MAGIC) - 1)) {
		return (true);
	}
	
	return (false);
}

static bool		is_fat_file(t_mach_o *ofile)
{
	struct fat_header	*fat_header;

	fat_header = ofile->addr;
	
	if (ofile->file_size <= sizeof(fat_header->magic))
		return (false);
	
	return 
		(fat_header->magic == FAT_MAGIC
			|| fat_header->magic == FAT_CIGAM
			|| fat_header->magic == FAT_MAGIC_64
			|| fat_header->magic == FAT_CIGAM_64);
}

static bool		is_macho_file(t_mach_o *ofile)
{
	struct mach_header		*header;
	struct mach_header_64	*header_64;

	header = ofile->addr;
	header_64 = ofile->addr;
	
	if (ofile->file_size <= sizeof(header->magic)
		|| ofile->file_size <= sizeof(header_64->magic)) {
		return (false);
	}
	
	return (header->magic == MH_MAGIC || header->magic == MH_CIGAM ||
			header_64->magic == MH_MAGIC_64 || header_64->magic == MH_CIGAM_64);
}

static bool		is_unknown(t_mach_o *ofile)
{
	(void)ofile;
	return (true);
}

static const t_map_file_type_checkers		g_types_map[SUPPORTED_OFILE_TYPES] = {
	{&is_archive_file, ARCHIVE_FILE},
	{&is_fat_file, FAT_FILE},
	{&is_macho_file, OBJECT_FILE},
	{&is_unknown, UNKNOWN},
};

/*
** Read the type of file from a t_mach_o structure
** Mach o file needs to have its filesize,
** its adress
** its magic number filled
*/

t_file_type	read_file_type(t_mach_o *ofile)
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