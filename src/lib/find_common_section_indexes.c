#include "mach_o_utils.h"

/*
** This file finds the common section of the file
** @TODO
*/

int32_t	nm_find_section(t_nm_process_info *nm_info,
                        char *segment_name,
                        char *section_name)
{
	uint32_t	i;

	assert(nm_info->secs || nm_info->secs_64);
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
	return (NO_SECT_FOUND);
}

inline void		find_common_sections_indexes()
{
	nm_info->text_nsect = nm_find_section(nm_info, SEG_TEXT, SECT_TEXT);
	nm_info->data_nsect = nm_find_section(nm_info, SEG_DATA, SECT_DATA);
	nm_info->bss_nsect = nm_find_section(nm_info, SEG_DATA, SECT_BSS);
}
