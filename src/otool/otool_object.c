#include "otool.h"

#include "ft_otool.h"

void				cleanup_otool_info(t_otool_dump *info)
{
	free(info->secs);
	free(info->secs_64);
	free(info->segs_64);
	free(info->segs);
}

int					init_otool_info(t_mach_o *file, t_otool_dump *otool_info)
{
	ft_bzero(info, sizeof(t_otool_info));
	if (ofile->mh && file->mh_64)
		return (-1);
	if (file->mh)
	{
		info->secs = ofile_get_sections(file, &info->nsects);
		info->segs = ofile_get_segments(file, &info->nsegs);
	}
	else
	{
		info->secs_64 = ofile_get_sections_64(file, &info->nsects);
		info->segs_64 = ofile_get_segments_64(file, &info->nsegs);
	}
	info->text_nsec = otool_find_section(info, SEG_TEXT, SECT_TEXT);
	return (0);
}

static int	otool_object_32(t_ofile *ofile, t_otool_dump *info)
{
	int			ret;

	ret = print_section(ofile, otool_info, otool_info->text_nsec);
	cleanup_otool_info(otool_info);
	if (ret == -1)
		return (mach_o_error(-1, "Truncated or malformed object file "
			"(the text section would go past the end of the file)\n"));
	return (0);
}

static int	otool_object_64(t_ofile *ofile, t_otool_dump *otool_info)
{
	int			ret;

	ret = print_section_64(ofile, otool_info, otool_info->text_nsec);
	cleanup_otool_info(otool_info);
	if (ret == -1)
		return (mach_o_error(-1, "Truncated or malformed object file "
			"(the text section would go past the end of the file)\n"));
	return (0);
}

int otool_object(t_mach_o *file, t_options *options)
{
	t_otool_dump	info;

	init_otool_info(ofile, &info);
    if (!info.secs && !info.secs_64)
        return (-1);
	if (info.text_nsec == NO_SECT_FOUND)
	{
		mach_o_error(-1, "There is no text section in the mach-o file\n");
		cleanup_otool_info(&info);
		return (-1);
	}
	return (info.secs ? 
        otool_object_32(ofile, &info)
        : otool_object_64(ofile, &info));
}
