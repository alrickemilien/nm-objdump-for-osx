#include "otool.h"

void		cleanup_otool_info(t_otool_dump *info)
{
	free(info->secs);
	free(info->secs_64);
	free(info->segs_64);
	free(info->segs);
}

int			init_otool_info(t_mach_o *file, t_otool_dump *info)
{
	ft_memset(info, 0, sizeof(t_otool_dump));
	if (file->mh && file->mh_64)
		return (-1);
	if (file->mh)
	{
		info->secs = read_sections_32(file, &info->nsects);
		info->segs = read_segments_32(file, &info->nsegs);
	}
	else
	{
		info->secs_64 = read_sections_64(file, &info->nsects);
		info->segs_64 = read_segments_64(file, &info->nsegs);
	}
	info->text_nsec = find_section(info, SEG_TEXT, SECT_TEXT);
	return (0);
}

static int	otool_object_32(t_mach_o *file, t_otool_dump *info)
{
	int			ret;

	ret = print_section_32(file, info, info->text_nsec);
	cleanup_otool_info(info);
	if (ret == -1)
		return (mach_o_error(-1, "Truncated or malformed object file "
			"(the text section would go past the end of the file)\n"));
	return (0);
}

static int	otool_object_64(t_mach_o *file, t_otool_dump *info)
{
	int			ret;

	ret = print_section_64(file, info, info->text_nsec);
	cleanup_otool_info(info);
	if (ret == -1)
		return (mach_o_error(-1, "Truncated or malformed object file "
			"(the text section would go past the end of the file)\n"));
	return (0);
}

int			otool_object(
		t_mach_o *file, t_options *options)
{
	t_otool_dump	info;

	(void)options;
	init_otool_info(file, &info);
	if (!info.secs && !info.secs_64)
		return (-1);
	if (info.text_nsec == NO_SECT_FOUND)
	{
		mach_o_error(-1, "There is no text section in the mach-o file\n");
		cleanup_otool_info(&info);
		return (-1);
	}
	return (info.secs ? 
		otool_object_32(file, &info)
		: otool_object_64(file, &info));
}
