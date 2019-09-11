#include "mach_o.h"

int32_t	check_file_addr(t_mach_o *file, void *addr)
{
	printf("file->addr %p\n", file->addr);
	printf("addr %p\n", addr);

	printf("(uint8_t*)file->addr + file->file_size %p\n", (uint8_t*)file->addr + file->file_size);
	printf("(uint8_t*)file->addr + file->file_size > (uint8_t*)addr : %d\n", (uint8_t*)file->addr + file->file_size > (uint8_t*)addr);

	if (file->addr <= addr
		&& ((uint8_t*)file->addr + file->file_size > (uint8_t*)addr
			|| (((uint64_t)file->addr + file->file_size - 1)
				& ~4095UL) == ((uint64_t)addr & ~4095UL)))
		return (0);
	return (-1);
}

int32_t	check_file_addr_size(t_mach_o *file,
	void *addr,
	uint64_t size)
{
	printf("\ncheck_file_addr(file, addr) %d\n", check_file_addr(file, addr));
	printf("size %lld\n", size);
	printf("check_file_addr(file, (uint8_t*)addr + size - 1) %d\n\n", check_file_addr(file, (uint8_t*)addr + size - 1));

	if (check_file_addr(file, addr) == 0
		&& (size == 0 || check_file_addr(file, (uint8_t*)addr + size - 1) == 0))
		return (0);
	return (-1);
}