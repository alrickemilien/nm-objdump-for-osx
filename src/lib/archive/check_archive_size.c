#include "mach_o.h"

int32_t	check_archive_addr(t_mach_o *file, void *addr)
{
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
	printf("\n =>>>>>>>>>>>>> addr is %p\n", addr);

	printf("check_file_addr_size(file, addr, size) : %d\n", check_file_addr_size(file, addr, size));
	printf("check_archive_addr(file, addr) : %d\n", check_file_addr_size(file, addr, size));
	printf("check_archive_addr(file, (uint8_t*)addr + size) : %d\n\n", check_file_addr_size(file, addr, size));

	if (check_file_addr_size(file, addr, size) == 0
		&& check_archive_addr(file, addr) == 0
		&& check_archive_addr(file, (uint8_t*)addr + size) == 0)
		return (0);
	return (-1);
}