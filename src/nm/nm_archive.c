#include "nm.h"

int32_t	nm_archive(t_mach_o *file, t_options *options)
{
	size_t  i;
	bool    error;

	LOGDEBUG("---- nm_archive\n");

	i = 0;
	error = 0;
	while (42)
	{
		LOGDEBUG ("---- nm_archive loop number %ld\n", i);

		if (load_archive_nth_member(file, i, &error) == -1)
		{
			LOGDEBUG ("INFO load_archive_nth_member error is %d\n", error);

			if (error)
				return (0);
			LOGDEBUG("%s", "Failed to load member\n");
			i++;
			continue ;
		}
		
		ft_printf("\n%s(%s):\n",
           	file->path,
           	file->archive_member_header.member_name);
		
        if (nm_object(file, options) == -1)
		{
			LOGDEBUG("INFO nm_archive ended zith code -1\n");
			// return (-1);
		}
		
        i++;
	}

	LOGDEBUG("INFO nm_archive ended zith code 0\n");

	return (0);
}