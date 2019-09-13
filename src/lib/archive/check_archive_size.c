#include "mach_o.h"

int32_t	check_archive_addr(t_mach_o *file, void *addr)
{
	LOGDEBUG("###### check_archive_addr \n"
		"file->addr %p\n"
		"file->file_size %lld\n"
		"file->archive_start_addr %p\n"
		"addr %p\n"
		"addr - file->archive_start_addr %p\n"
		"addr - file->size %p\n",
		file->addr,
		file->file_size,
		file->archive_start_addr,
		addr,
		(void*)((uint8_t*)addr - (uint8_t*)file->archive_start_addr),
		(void*)((uint8_t*)addr - (uint8_t*)file->addr));

	if (file->archive_start_addr == NULL)
		return (-1);
	if (addr < file->archive_start_addr || addr < file->addr
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->archive_start_addr) > file->archive_size
		|| (uint64_t)((uint8_t*)addr - (uint8_t*)file->addr) > file->file_size)
		return (-1);
	return (0);
}

int32_t	check_archive_addr_size(t_mach_o *file,
								void *addr,
								uint64_t size)
{
	LOGDEBUG("#### check_archive_addr_size with size at %lld\n", size);

	if (check_file_addr_size(file, addr, size) == 0
		&& check_archive_addr(file, addr) == 0
		&& check_archive_addr(file, (uint8_t*)addr + size) == 0)
		return (0);
	LOGDEBUG("check_archive_addr_size return -1\n");
	return (-1);
}