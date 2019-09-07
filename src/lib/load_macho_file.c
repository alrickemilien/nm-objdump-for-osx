#include "mach_o.h"


typedef struct s_map_type_to_loaders {
	bool			(*loader)(t_mach_o *ofile);
	uint32_t		type;
}				t_map_type_to_loaders;

static const t_map_type_to_loaders	g_file_loaders_map[] = {
	{&load_archive_file, ARCHIVE_FILE},
	{&load_fat_file, FAT_FILE},
	{&load_object_file, OBJECT_FILE},
	{&is_unknown, UNKNOWN}
};

/*
** Load mach-o-file informations
** - Load its map adresses in memory
** - Load its magick number
** - Load the entire file informations according to file type
*/

int	load_macho_file(
	t_mach_o *file,
	char *path,
	void *addr,
	uint64_t file_size)
{
	size_t					i;
	
	file->addr = addr;
	file->file_size = file_size;
	file->path = path;
	
	file->type = read_file_type(file);
	
	if (file->fat_header)
		file->arch_type = file->type;

	i = 0;
	while (i < sizeof(g_file_loaders_map) / sizeof(t_map_type_to_loaders))
	{
		if (g_file_loaders_map[i].loader(file))
			return (g_file_loaders_map[i].type);
		i++;
	}

	return mach_o_error(MACH_O_ERROR_INVALID_FILE_TYPE);
}