
inline static void	swap_fat_header(struct fat_header *fat_hdr)
{
	fat_hdr->magic = swap_int32(fat_hdr->magic);
	fat_hdr->nfat_arch = swap_int32(fat_hdr->nfat_arch);
}

inline static void	swap_fat_arch_32(struct fat_arch *fat_arch)
{
	fat_arch->cputype = (cpu_type_t)swap_int32(
		(uint32_t)fat_arch->cputype);
	fat_arch->cpusubtype = (cpu_subtype_t)swap_int32(
		(uint32_t)fat_arch->cpusubtype);
	fat_arch->offset = swap_int32(fat_arch->offset);
	fat_arch->size = swap_int32(fat_arch->size);
	fat_arch->align = swap_int32(fat_arch->align);
}

inline static void	swap_fat_arch_64(struct fat_arch_64 *fat_arch_64)
{
	fat_arch_64->cputype = (cpu_type_t)swap_int32(
		(uint32_t)fat_arch_64->cputype);
	fat_arch_64->cpusubtype = (cpu_subtype_t)swap_int32(
		(uint32_t)fat_arch_64->cpusubtype);
	fat_arch_64->offset = swap_int64(fat_arch_64->offset);
	fat_arch_64->size = swap_int64(fat_arch_64->size);
	fat_arch_64->align = swap_int32(fat_arch_64->align);
	fat_arch_64->reserved = swap_int32(fat_arch_64->reserved);
}

inline static void	swap_fat_archs_header(t_mach_o *ofile, uint32_t narch)
{
	assert(ofile->fat_archs || ofile->fat_archs_64);
	assert(sizeof(ofile->fat_archs->cputype) == sizeof(int32_t));
	assert(sizeof(ofile->fat_archs->cpusubtype) == sizeof(int32_t));
	if (ofile->fat_archs)
		swap_fat_arch_32(&ofile->fat_archs[narch]);
	else
		swap_fat_arch_64(&ofile->fat_archs_64[narch]);
}

int32_t				ofile_swap_fat_headers(t_mach_o *ofile)
{
	uint32_t	i;

	assert(ofile->fat_header);
	assert(ofile->fat_archs || ofile->fat_archs_64);
	swap_fat_header(ofile->fat_header);
	i = 0;
	while (i < ofile->fat_header->nfat_arch)
	{
		if ((ofile->fat_archs
			&& -1 == ofile_file_check_addr_size(ofile, ofile->fat_archs + i,
												sizeof(struct fat_arch)))
			|| (ofile->fat_archs_64
			&& -1 == ofile_file_check_addr_size(ofile, ofile->fat_archs_64 + i,
												sizeof(struct fat_arch_64))))
		{
			dprintf(2, "%s: %s",
					ofile->file_name, ERR_UNKNOWN_FILE_FORMAT);
			return (-1);
		}
		swap_fat_archs_hdr(ofile, i);
		i++;
	}
	return (0);
}