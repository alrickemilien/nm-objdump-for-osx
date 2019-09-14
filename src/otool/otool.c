#include "otool.h"

static int	dispatch(t_mach_o *file, t_options *options)
{
	if (file->type == OBJECT_FILE)
	{
		ft_printf("%s:\n", file->path);
		return (otool_object(file, options));
	}
	else if (file->type == FAT_FILE)
		return (otool_fat_archive(file, options));
	else if (file->type == ARCHIVE_FILE)
	{
		ft_printf("Archive : %s\n", file->path);
		return (otool_archive(file, options));
	}
	return (-1);
}

int	otool(t_options *options, const char *path)
{
	t_mach_o	file;
	int			error;

	ft_memset(&file, 0, sizeof(t_mach_o));

	// 1) Load the files
	if ((file.addr = map_loading_file(path, &file.file_size)) == NULL)
		return (-1);

	// 2) Read file type
	if (load_macho_file(&file, path, file.addr, file.file_size) < 0)
		return (mach_o_error(-1, OTOOL_DEFAULT_MACHO_ERROR, file.path));

	if (file.type == UNKNOWN_FILE)
		return (mach_o_error(-1, "%s: %s Unknown file format\n", path, path));
	error = dispatch(&file, options);
	if (map_unloading_file(file.addr, file.file_size))
		return (-1);
	return (error);
}