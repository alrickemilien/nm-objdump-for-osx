#include "mach_o.h"

static int32_t	read_object(t_mach_o *file)
{
	file->endian = read_object_endian(
		((struct mach_header *)file->o_addr));
	if (file->endian == UNKNOWN_ENDIAN)
	{
		dprintf(2, "Unknown endian found for mach-o object, aborting...\n");
		return (-1);
	}
	if (file->endian != endian())
		file->must_be_swapped = true;
	else
		file->must_be_swapped = false;
	if (read_object_header(file) == NULL)
	{
		dprintf(2, "Malformed object file, "
				"the mach-o header is truncated or non-existant\n");
		return (-1);
	}
	if (read_object_load_commands(file) == NULL)
	{
		dprintf(2, "Malformed object file, there are no load commands\n");
		return (-1);
	}
	return (0);
}

int32_t			load_object_file(t_mach_o *file,
						void *object_addr,
						uint64_t object_size)
{
	file->o_addr = object_addr;
	file->o_size = object_size;
	if (-1 == check_file_addr_size(file,
						file->o_addr,
						file->o_size))
		return (-1);
	if (read_object(file) == -1)
		return (-1);
	if (file->must_be_swapped)
	{
		swap_object_header(file);
		if (swap_all_load_commands(file) == -1)
			return (-1);
	}
	if (check_object_integrity(file) == -1)
		return (-1);
	if (file->must_be_swapped)
		swap_symtab(file);
	return (0);
}
