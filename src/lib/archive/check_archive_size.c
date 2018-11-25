#include "mach_o_utils.h"

int32_t	check_archive_addr(t_mach_o *ofile, void *addr)
{
	if (NULL == ofile->archive_start_addr)
		return (-1);

	// When the adress is before (outside) the archive adress or the file adress itself
	// Not valid, return -1
	if (addr < ofile->archive_start_addr || addr < ofile->addr)
		return (-1);

	// When the adress is after the archive size or the file size itself
	// Not valid, return -1
	if ((uint64_t)((uint8_t*)addr - (uint8_t*)ofile->archive_start_addr)
			> ofile->archive_size
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)ofile->addr)
			> ofile->file_size)
	{
		return (-1);
	}

	return (0);
}

int32_t	check_archive_addr_size(t_mach_o *ofile,
								void *addr,
								uint64_t size)
{
	if (check_file_addr_size(ofile, addr, size) == 0
		&& check_archive_addr(ofile, addr) == 0
		&& check_archive_addr(ofile, (uint8_t*)addr + size) == 0)
		return (0);
	return (-1);
}