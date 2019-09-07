#include "nm.h"

int32_t	nm_archive(t_mach_o *file, t_options *options)
{
	size_t  i;
	bool    error;

	i = 0;
	error = 0;
	while (42)
	{
		if (ofile_load_narchive_member(file, i, &error) == -1)
		{
			if (error)
				return (0);
			printf("Failed to load member\n");
			i++;
			continue ;
		}
		printf("\n%s(%s):\n",
            file->path,
            file->archive_member_header.member_name);
		
        if (nm_object(file, options) == -1)
			return (-1);
		
        i++;
	}
}