#include "nm.h"
#include <mach-o/arch.h>

int32_t			find_current_arch(t_mach_o *file, t_options *options)
{
	if (ofile->arch_ofile_type == OFILE_MACHO)
		return (nm_process_obj(ofile, flags));
	else if (ofile->arch_ofile_type == OFILE_FAT)
		return (nm_handle_fat(ofile, flags));
	else if (ofile->arch_ofile_type == OFILE_ARCHIVE)
		return (nm_handle_archive(ofile, flags));
	return (-1);
}

static int32_t	nm_all_fat_archs(t_mach_o *file, t_options *options)
{
	size_t  i;

	i = 0;
	while (i < file->fat_header->nfat_arch)
	{
		if (ofile_load_narch(file, i) == -1)
		{
			i++;
			continue ;
		}
		if (file->fat_header->nfat_arch != 1)
			printf("\n%s (for architecture %s):\n", file->file_name,
				get_cputype_name(file->fat_archs ? file->fat_archs[i].cputype
									: file->fat_archs_64[i].cputype));
		else
			printf("%s:\n", file->file_name);
		if (find_current_arch(file, flags) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int32_t			nm_fat_archive(t_mach_o *file, t_options *options)
{
	int32_t				narch_for_arch;
	const NXArchInfo	*host_arch;

	host_arch = NXGetLocalArchInfo();
	if (-1 == (narch_for_arch = ofile_fat_find_arch(ofile,
		host_arch->cputype | CPU_ARCH_ABI64, host_arch->cpusubtype)))
		return (nm_all_fat_archs(ofile, flags));
	else
	{
		if (ofile_load_narch(file, (uint32_t)narch_for_arch) == -1)
			return (-1);
		return (find_current_arch(file, flags));
	}
}
