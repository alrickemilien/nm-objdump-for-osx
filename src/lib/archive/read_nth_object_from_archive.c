
inline static int32_t	load_narch_32(t_ofile *ofile, uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (-1 == ofile_file_check_addr_size(ofile, ofile->fat_archs + narch,
										sizeof(struct fat_arch)))
	{
		ft_dprintf(2, ERR_FAT_HDR_TRUNC);
		return (-1);
	}
	addr = (void *)((uint8_t *)ofile->vm_addr +
					ofile->fat_archs[narch].offset);
	object_size = ofile->fat_archs[narch].size;
	return (ofile_load_file(ofile, addr, object_size));
}

inline static int32_t	load_narch_64(t_ofile *ofile, uint32_t narch)
{
	void		*addr;
	uint64_t	object_size;

	if (-1 == ofile_file_check_addr_size(ofile, ofile->fat_archs_64 + narch,
										sizeof(struct fat_arch_64)))
	{
		ft_dprintf(2, ERR_FAT_HDR_TRUNC);
		return (-1);
	}
	addr = (void *)((uint8_t *)ofile->vm_addr +
					ofile->fat_archs_64[narch].offset);
	object_size = ofile->fat_archs_64[narch].size;
	return (ofile_load_file(ofile, addr, object_size));
}

int32_t					ofile_load_narch(t_ofile *ofile, uint32_t narch)
{
	assert(narch < ofile->fat_header->nfat_arch);
	assert(ofile->fat_archs || ofile->fat_archs_64);
	
	if (narch >= ofile->fat_header->nfat_arch)
		return (-1);
	
	ofile->object_addr = NULL;
	ofile->object_size = 0;
	ofile->obj_byte_sex = UNKNOWN_BYTE_SEX;
	ofile->must_be_swapped = false;
	ofile->mh = NULL;
	ofile->mh_64 = NULL;
	ofile->load_commands = NULL;
	ofile->narch = narch;
	
	if (ofile->fat_archs)
		return (load_narch_32(ofile, narch));

	return (load_narch_64(ofile, narch));
}
