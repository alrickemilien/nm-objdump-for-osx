#include "mach_o.h"

int	find_fat_archive_architecture(t_mach_o *file,
							cpu_type_t cputype,
							cpu_subtype_t subtype)
{
	size_t	i;

	if (!file->fat_header || (!file->fat_archs && !file->fat_archs_64))
		return (-1);
	
	i = 0;
	(void)subtype;
	while (i < file->fat_header->nfat_arch)
	{
		if (check_file_addr_size(file,
			(file->fat_archs ? (void *)file->fat_archs : (void *)file->fat_archs_64),
			sizeof(struct fat_arch_64)) == -1) 
		{
			return (-1);
		}

		if (file->fat_archs && file->fat_archs[i].cputype == cputype)
		{
			return ((int32_t)i);
		}
		
		else if (file->fat_archs_64 && file->fat_archs_64[i].cputype)
		{
			return ((int32_t)i);
		}
		
		i++;
	}
	return (-1);
}