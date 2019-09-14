#include "mach_o.h"


typedef struct s_map_type_to_loaders {
	int32_t			(*loader)(t_mach_o *ofile, void *addr, uint64_t size);
	uint32_t		type;
}				t_map_type_to_loaders;

static const t_map_type_to_loaders	g_file_loaders_map[] = {
	{&load_archive_file, ARCHIVE_FILE},
	{&load_fat_archive_file, FAT_FILE},
	{&load_object_file, OBJECT_FILE},
};

/*
** Load mach-o-file informations
** - Load its map adresses in memory
** - Load its magick number
** - Load the entire file informations according to file type
*/

int	load_macho_file(
	t_mach_o *file,
	const char *path,
	void *addr,
	uint64_t file_size)
{
	size_t	i;
	
	file->o_addr = addr;
	file->o_size = file_size;
	file->path = path;
	
	file->type = read_file_type(file);
	
	if (file->fat_header)
		file->arch_type = file->type;

	i = 0;
	while (i < SUPPORTED_FILE_TYPES)
	{
		if (file->type == g_file_loaders_map[i].type)
			return (g_file_loaders_map[i].loader(file, addr, file_size));
		i++;
	}
	// Invalid file type
	return (-1);
}