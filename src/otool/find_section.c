#include "otool.h"

uint32_t	find_section(
	t_otool_dump *info,
	char *seg_name,
	char *sec_name)
{
	size_t	i;

	if (!info->secs && !info->secs_64)
		return (-1);
	i = 0;
	if (info->secs)
	{
		while (i < info->nsects)
		{
			if (ft_strequ(seg_name, info->secs[i]->segname)
				&& ft_strequ(sec_name, info->secs[i]->sectname))
				return (i);
			i++;
		}
	}
	else
	{
		while (i < info->nsects)
		{
			if (ft_strequ(seg_name, info->secs_64[i]->segname)
				&& ft_strequ(sec_name, info->secs_64[i]->sectname))
				return (i);

			i++;
		}
	}
	return (-1);
}