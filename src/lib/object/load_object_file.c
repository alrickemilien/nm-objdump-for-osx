#include "mach_o.h"

static int32_t	set_file_mh_values(t_ofile *ofile)
{
	ofile->endian = get_macho_byte_sex(
		((struct mach_header *)ofile->object_addr));
	if (ofile->endian == UNKNOWN_BYTE_SEX)
	{
		ft_dprintf(2, "Unknown endian found for mach-o object, aborting...\n");
		return (-1);
	}
	if (ofile->endian != endian())
		ofile->must_be_swapped = true;
	else
		ofile->must_be_swapped = false;
	if (set_ofile_mh(ofile) == NULL)
	{
		ft_dprintf(2, "Malformed object file, "
				"the mach-o header is truncated or non-existant\n");
		return (-1);
	}
	if (set_ofile_load_commands(ofile) == NULL)
	{
		ft_dprintf(2, "Malformed object file, there are no load commands\n");
		return (-1);
	}
	return (0);
}

int32_t			load_macho_ofile(t_ofile *ofile,
						void *object_addr,
						uint64_t object_size)
{
	ofile->object_addr = object_addr;
	ofile->object_size = object_size;
	if (-1 == ofile_file_check_addr_size(ofile,
										ofile->object_addr,
										ofile->object_size))
		return (-1);
	if (set_ofile_mh_values(ofile) == -1)
		return (-1);
	if (ofile->must_be_swapped)
	{
		ofile_swap_macho_hdr(ofile);
		if (-1 == ofile_swap_macho_load_commands(ofile))
			return (-1);
	}
	if (ofile_check_object_integrity(ofile) == -1)
		return (-1);
	if (ofile->must_be_swapped)
		ofile_swap_macho_symtab(ofile);
	return (0);
}
