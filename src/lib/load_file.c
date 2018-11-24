#include "mach_o_utils.h"

int	ofile_load_file(t_ofile *ofile, void *object_addr, uint64_t object_size)
{
	ofile->object_addr = object_addr;
	
	ofile->ofile_type = get_ofile_type(ofile);
	
	if (ofile->fat_header)
		ofile->arch_ofile_type = ofile->ofile_type;
	
	if (ofile->ofile_type == OFILE_FAT)
	{
		if (-1 == load_fat_ofile(ofile))
			return (-1);
	}
	else if (ofile->ofile_type == OFILE_ARCHIVE)
	{
		if (-1 == load_archive_file(ofile, object_addr, object_size))
			return (-1);
	}
	else if (ofile->ofile_type == OFILE_MACHO)
	{
		if (-1 == load_macho_ofile(ofile, object_addr, object_size))
			return (-1);
	}
	return (0);
}