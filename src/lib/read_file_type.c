#include "mach_o.h"

/*
** This file provides functions that read the file type
** (archive, fat arch, macho file)
** WARNING
** Do not mix file type (archive, fat arch, macho file)
** and macho file type (MH_OBJECT, MH_EXECUTE, MH_FVMLIB)
** specific for macho file header
*/

typedef struct s_map_type_to_checkers {
	bool			(*checker)(t_mach_o *file);
	int				file_type;
}				t_map_type_to_checkers;

static bool		is_archive_file(t_mach_o *file)
{
	if (file->file_size <= sizeof(STATIC_LIB_MAGIC)) {
		return (false);
	}
	
	if (!memcmp(
			file->o_addr,
			STATIC_LIB_MAGIC,
			sizeof(STATIC_LIB_MAGIC) - 1)) {
		return (true);
	}
	
	return (false);
}

static bool		is_fat_file(t_mach_o *file)
{
	struct fat_header	*fat_header;

	fat_header = file->o_addr;
	
	if (file->file_size <= sizeof(fat_header->magic))
		return (false);
	
	return (fat_header->magic == FAT_MAGIC
			|| fat_header->magic == FAT_CIGAM
			|| fat_header->magic == FAT_MAGIC_64
			|| fat_header->magic == FAT_CIGAM_64);
}

static bool		is_macho_file(t_mach_o *file)
{
	struct mach_header		*header;
	struct mach_header_64	*header_64;

	header = file->o_addr;
	header_64 = file->o_addr;
	
	if (file->file_size <= sizeof(header->magic)
		|| file->file_size <= sizeof(header_64->magic))
		return (false);
	
	return (header->magic == MH_MAGIC || header->magic == MH_CIGAM ||
			header_64->magic == MH_MAGIC_64 || header_64->magic == MH_CIGAM_64);
}

static bool		is_unknown(t_mach_o *file)
{
	(void)file;
	return (true);
}

static const t_map_type_to_checkers		g_types_map[] = {
	{&is_archive_file, ARCHIVE_FILE},
	{&is_fat_file, FAT_FILE},
	{&is_macho_file, OBJECT_FILE},
	{&is_unknown, UNKNOWN_FILE},
};

/*
** Read the type of file from a t_mach_o structure
** Mach o file needs to have its filesize,
** its adress
** its magic number filled
*/

unsigned	read_file_type(t_mach_o *file)
{
	size_t	i;

	i = 0;
	while (i < SUPPORTED_FILE_TYPES)
	{
		if (g_types_map[i].checker(file))
			return (g_types_map[i].file_type);
		i++;
	}

	return (UNKNOWN_FILE);
}