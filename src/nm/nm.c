#include "nm.h"

static int	dispatch(t_mach_o *file, t_options *options)
{
	if (file->type == OBJECT_FILE)
		return (nm_object(file, options));
	else if (file->type == FAT_FILE)
		return (nm_fat_archive(file, options));
	else if (file->type == ARCHIVE_FILE)
		return (nm_archive(file, options));
	return (-1);
}

int	nm(t_options *options, const char *path)
{
	t_mach_o	file;
	int			error;

	ft_memset(&file, 0, sizeof(t_mach_o));

	// 1) Load the files
	if ((file.addr = map_loading_file(path, &file.file_size)) == NULL)
		return (-1);

	// 2) Read file type
	if (load_macho_file(&file, path, file.addr, file.file_size) < 0)
		return (mach_o_error(-1, NM_DEFAULT_MACHO_ERROR, file.path));

	if (file.type == UNKNOWN_FILE)
		return (mach_o_error(NOT_RECOGNIZED_VALID_FILE_EXIT_CODE, "%s: %s Unknown file format\n", path, path));
	if (options->file_count > 1 && file.type == OBJECT_FILE)
		ft_printf("\n%s:\n", path);
	error = dispatch(&file, options);
	if (map_unloading_file(file.addr, file.file_size))
		return (-1);
	return (error);
}