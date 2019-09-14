#include "mach_o.h"

int	check_file_addr(t_mach_o *file, void *addr)
{
	LOGDEBUG("###### check_file_addr\n"
		"file->addr %p\n"
		"file->file_size %lld\n"
		"addr %p\n"
		"(uint8_t*)file->addr + file->file_size %p\n"
		, file->addr, file->file_size, addr, ((uint8_t*)file->addr + file->file_size));

	if (file->addr <= addr
		&& ((uint8_t*)file->addr + file->file_size > (uint8_t*)addr
			|| (((uint64_t)file->addr + file->file_size - 1)
				& ~4095UL) == ((uint64_t)addr & ~4095UL)))
		return (0);
	return (-1);
}

int	check_file_addr_size(t_mach_o *file,
	void *addr,
	uint64_t size)
{
	LOGDEBUG("##### check_file_addr_size with size at %lld\n", size);
	if (check_file_addr(file, addr) == 0
		&& (size == 0 || check_file_addr(file, (uint8_t*)addr + size - 1) == 0))
		return (0);
	LOGDEBUG("%s", "check_file_addr_size return -1\n");
	return (-1);
}