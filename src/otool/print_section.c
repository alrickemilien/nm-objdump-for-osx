#include "otool.h"

static void		print_sections_line_32(void *addr,
								uint32_t bytes_number,
								cpu_type_t cputype)
{
	size_t  i;

	i = 0;
	if (cputype != CPU_TYPE_POWERPC)
    {
        while (i < bytes_number)
			ft_printf("%02x ", ((uint8_t*)addr)[i++]);
    }
	else
    {
		while (i < bytes_number)
		{
			ft_printf("%08x ", swap_int32(((uint32_t*)addr)[i / 4]));
			i += 4;
		}
    }
	ft_printf("\n");
}

int			print_section_32(t_mach_o *file,
							t_otool_dump *info,
							uint32_t nsec)
{
	void		*section_addr;
	uint32_t    size;
	uint32_t    i;

    if (!info->secs || info->segs)
        return (-1);
	if (check_object_addr_size(file,
				(uint8_t*)file->o_addr + info->secs[nsec]->offset,
				info->secs[nsec]->size) == -1)
		return (-1);
	section_addr = (void *)((uint8_t*)file->o_addr
							+ info->secs[nsec]->offset);
	size = info->secs[nsec]->size;
	i = 0;
	ft_printf("Contents of (%s,%s) section\n", info->secs[nsec]->segname,
										info->secs[nsec]->sectname);
	while (i < size)
	{
		ft_printf("%08x\t", info->secs[nsec]->addr + i);
		print_sections_line_32((uint8_t*)section_addr + i,
						size - i > 16 ? 16 : size - i
						, file->mh->cputype);
		i += 16;
	}
	return (0);
}

static void		print_sections_line_64(void *addr, uint64_t bytes_number)
{
	size_t	i;

	i = 0;
	while (i < bytes_number)
		ft_printf("%02x ", ((uint8_t*)addr)[i++]);
	ft_printf("\n");
}

int			print_section_64(t_mach_o *file, t_otool_dump *info, uint32_t nsec)
{
	void		*section_addr;
	uint64_t    size;
	uint64_t    i;

	if (!info->secs_64 || !info->segs_64)
        return (-1);
	if (check_object_addr_size(file,
			(uint8_t*)file->o_addr + info->secs_64[nsec]->offset,
			info->secs_64[nsec]->size) == -1)
		return (-1);
	section_addr = (void *)((uint8_t*)file->o_addr
							+ info->secs_64[nsec]->offset);
	size = info->secs_64[nsec]->size;
	i = 0;
	ft_printf("Contents of (%s,%s) section\n",
			info->secs_64[nsec]->segname,
			info->secs_64[nsec]->sectname);
	while (i < size)
	{
		ft_printf("%016llx\t", info->secs_64[nsec]->addr + i);
		print_sections_line_64((uint8_t*)section_addr + i,
						size - i > 16 ? 16 : size - i);
		i += 16;
	}
	return (0);
}
