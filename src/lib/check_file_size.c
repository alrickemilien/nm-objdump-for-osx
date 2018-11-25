#include "mach_o_utils.h"

int32_t	check_file_addr(t_mach_o *ofile, void *addr)
{
	if (ofile->vm_addr <= addr
		&& ((uint8_t*)ofile->vm_addr + ofile->file_size > (uint8_t*)addr
			|| (((uint64_t)ofile->vm_addr + ofile->file_size - 1)
				& ~4095UL) == ((uint64_t)addr & ~4095UL)))
		return (0);
	return (-1);
}

int32_t	check_file_addr_size(t_mach_o *ofile,
											void *addr,
											uint64_t size)
{
	if (check_file_addr(ofile, addr) == 0
	&& (size == 0 || check_file_addr(ofile, (uint8_t*)addr + size - 1) == 0))
		return (0);
	return (-1);
}