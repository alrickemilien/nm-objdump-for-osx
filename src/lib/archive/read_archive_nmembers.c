#include "mach_o.h"

static bool		is_ran_off_already_in_ranlibs(t_mach_o *file,
										struct ranlib *ranlib,
										uint64_t index)
{
	uint64_t	i;

	i = 0;
	// assert(file->ranlibs && index < file->nran);
	while (i < index)
	{
		if (file->ranlibs[i].ran_off == ranlib->ran_off)
			return (true);
		i++;
	}
	return (false);
}

static bool		is_ran_off_already_in_ranlibs_64(t_mach_o *file,
											struct ranlib_64 *ranlib,
											uint64_t index)
{
	uint64_t	i;

	i = 0;
	// assert(file->ranlibs_64 && index < file->nran);
	while (i < index)
	{
		if (file->ranlibs_64[i].ran_off == ranlib->ran_off)
			return (true);
		i++;
	}
	return (false);
}

static uint64_t	read_archive_nmembers_32(t_mach_o *file)
{
	uint64_t		nmembers;
	uint64_t		i;

	nmembers = file->nran;
	i = 0;
	while (i < file->nran)
	{
		if (is_ran_off_already_in_ranlibs(file, file->ranlibs + i, i))
			nmembers--;
		i++;
	}
	return (nmembers);
}

static uint64_t	read_archive_nmembers_64(t_mach_o *file)
{
	uint64_t		nmembers;
	uint64_t		i;

	nmembers = file->nran;
	i = 0;
	while (i < file->nran)
	{
		if (is_ran_off_already_in_ranlibs_64(file, file->ranlibs_64 + i, i))
			nmembers--;
		i++;
	}
	return (nmembers);
}

uint64_t		read_archive_nmembers(t_mach_o *file)
{
	// assert(file->ranlibs || file->ranlibs_64);
	if (file->ranlibs)
		return (read_archive_nmembers_32(file));
	else
		return (read_archive_nmembers_64(file));
}
