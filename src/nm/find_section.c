#include "nm.h"

uint32_t	find_section(
	t_mach_o_processor *nm_info,
	char *seg_name,
	char *sec_name)
{
	size_t	i;

	if (!nm_info->secs && !nm_info->secs_64)
		return (-1);
	i = 0;
	if (nm_info->secs)
	{
		while (i < nm_info->nsects)
		{
			if (ft_strequ(seg_name, nm_info->secs[i]->segname)
				&& ft_strequ(sec_name, nm_info->secs[i]->sectname))
				return (i);
			i++;
		}
	}
	else
	{
		while (i < nm_info->nsects)
		{
			if (ft_strequ(seg_name, nm_info->secs_64[i]->segname)
				&& ft_strequ(sec_name, nm_info->secs_64[i]->sectname))
				return (i);
			i++;
		}
	}
	return (MACH_O_ERROR_NO_SECTION_FOUND);
}