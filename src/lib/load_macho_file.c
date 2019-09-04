#include "mach_o.h"


typedef struct s_map_file_type_loaders {
	bool			(*loader)(t_mach_o *ofile);
	t_file_type		file_type;
}				t_map_file_type_loaders;

static const t_map_file_type_checkers		g_file_loaders_map[SUPPORTED_OFILE_TYPES] = {
	{&load_archive_file, ARCHIVE_FILE},
	{&load_fat_file, FAT_FILE},
	{&load_object_file, OBJECT_FILE},
	{&is_unknown, UNKNOWN},
};

/*
** Load mach-o-file informations
** - Load its map adresses in memory
** - Load its magick number
** - Load the entire file informations according to file type
*/

int	load_macho_file(
	t_mach_o *ofile,
	char *path,
	void *addr,
	uint64_t file_size)
{
	uint32_t						i;
	
	ofile->addr = addr;
	ofile->file_size = file_size;
	ofile->path = path;
	
	ofile->file_type = read_file_type(ofile);
	
	if (ofile->fat_header)
		ofile->arch_ofile_type = ofile->ofile_type;

	i = 0;
	while (i < SUPPORTED_OFILE_TYPES)
	{
		if (g_types_map[i].checker(ofile))
			return (g_types_map[i].file_type);
		i++;
	}

	return mach_o_error(MACH_O_ERROR_INVALID_FILE_TYPE);
}