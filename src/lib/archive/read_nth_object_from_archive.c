#include "mach_o.h"

static  int32_t	load_narch_32(t_mach_o *file, uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (check_file_addr_size(file, file->fat_archs + narch,
								sizeof(struct fat_arch)) == -1)
	{
		dprintf(2, MACH_O_ERROR_HEADER_TRUNCATED_STR);
		return (-1);
	}
	addr = (void *)((uint8_t *)file->addr +
					file->fat_archs[narch].offset);
	object_size = file->fat_archs[narch].size;
	return (load_macho_file(file, addr, file->path, object_size));
}

static  int32_t	load_narch_64(t_mach_o *file, uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (check_file_addr_size(file, file->fat_archs_64 + narch,
									sizeof(struct fat_arch_64)) == -1)
	{
		dprintf(2, MACH_O_ERROR_HEADER_TRUNCATED_STR);
		return (-1);
	}
	addr = (void *)((uint8_t *)file->addr +
					file->fat_archs_64[narch].offset);
	object_size = file->fat_archs_64[narch].size;
	return (load_macho_file(file, addr, file->path, object_size));
}

int32_t					file_load_narch(t_mach_o *file, uint32_t narch)
{
	// assert(narch < file->fat_header->nfat_arch);
	// assert(file->fat_archs || file->fat_archs_64);
	
	if (narch >= file->fat_header->nfat_arch)
		return (-1);
	
	file->o_addr = NULL;
	file->o_size = 0;
	// file->obj_byte_sex = UNKNOWN_BYTE_SEX;
	file->must_be_swapped = false;
	file->mh = NULL;
	file->mh_64 = NULL;
	file->load_commands = NULL;
	file->narch = narch;
	
	if (file->fat_archs)
		return (load_narch_32(file, narch));

	return (load_narch_64(file, narch));
}
