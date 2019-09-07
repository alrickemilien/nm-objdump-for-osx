#include "nm.h"

static int32_t	dispatch(t_mach_o *file, t_options *options)
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

	// 1) Load the files
	if ((file.addr = map_loading_file(path, &file.file_size)) == NULL)
		return (EXIT_FAILURE);

	if (file.type == UNKNOWN_FILE)
	{
		dprintf(2, "%s: %s %s\n", path, path,
				MACH_O_ERROR_UNKKNOWN_FILE_FORMAT_STR);
        return (0);
	}
	// if (nm_flags->nbr_files > 1)
	// 	printf("\n%s:\n", path);
	dispatch(&file, options);
	if (map_unloading_file(file.addr, file.file_size))
		return (EXIT_FAILURE);
	return (0);
}