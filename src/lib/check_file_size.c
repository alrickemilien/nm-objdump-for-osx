#include "mach_o.h"

int32_t	check_file_addr(t_mach_o *file, void *addr)
{
	if (file->vm_addr <= addr
		&& ((uint8_t*)file->vm_addr + file->file_size > (uint8_t*)addr
			|| (((uint64_t)file->vm_addr + file->file_size - 1)
				& ~4095UL) == ((uint64_t)addr & ~4095UL)))
		return (0);
	return (-1);
}

int32_t	check_file_addr_size(t_mach_o *file,
	void *addr,
	uint64_t size)
{
	if (check_file_addr(file, addr) == 0
	&& (size == 0 || check_file_addr(file, (uint8_t*)addr + size - 1) == 0))
		return (0);
	return (-1);
}