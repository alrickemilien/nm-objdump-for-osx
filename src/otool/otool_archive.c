#include "otool.h"

int	otool_archive(t_mach_o *file, t_options *options)
{
	size_t	i;
	bool	error;

	i = 0;
	error = 0;
	while (42)
	{
		if (load_archive_nth_member(file, i, &error) == -1)
		{
			if (error)
				return (0);
			else
				return (mach_o_error(
				-1, OTOOL_DEFAULT_MACHO_ERROR, file->path));
		}
		ft_printf("%s(%s):\n",
			file->path,
			file->archive_member_header.member_name);
		if (otool_object(file, options) == -1)
			return (-1);
		i++;
	}
}
