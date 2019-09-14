#include "mach_o.h"

static int	load_fat_archive_nth_arch_32(
    t_mach_o *file,
    uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (check_file_addr_size(file, file->fat_archs + narch,
								sizeof(struct fat_arch)) == -1)
		return (mach_o_error(-1, "Truncated fat archive"));
	addr = (void *)((uint8_t *)file->addr +
					file->fat_archs[narch].offset);
	object_size = file->fat_archs[narch].size;
	return (load_macho_file(file, file->path, addr, object_size));
}

static int	load_fat_archive_nth_arch_64(
    t_mach_o *file,
    uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (check_file_addr_size(file, file->fat_archs_64 + narch,
								sizeof(struct fat_arch_64)) == -1)
		return (mach_o_error(-1, "Truncated fat archive"));
	addr = (void *)((uint8_t *)file->addr +
					file->fat_archs_64[narch].offset);
	object_size = file->fat_archs_64[narch].size;
	return (load_macho_file(file, file->path, addr, object_size));
}

int         load_fat_archive_nth_arch(
    t_mach_o *file,
    uint32_t narch)
{
	if (narch > file->fat_header->nfat_arch)
		return (-1);
	if (!file->fat_archs && !file->fat_archs_64)
		return (-1);
	if (narch >= file->fat_header->nfat_arch)
		return (-1);
	file->o_addr = NULL;
	file->o_size = 0;
	file->o_endian = UNKNOWN_ENDIAN;
	file->must_be_swapped = false;
	file->mh = NULL;
	file->mh_64 = NULL;
	file->load_commands = NULL;
	file->narch = narch;
	if (file->fat_archs)
		return (load_fat_archive_nth_arch_32(file, narch));
	else
		return (load_fat_archive_nth_arch_64(file, narch));
}