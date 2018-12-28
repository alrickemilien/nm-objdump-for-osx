
static bool		is_ran_off_already_in_ranlibs(t_ofile *ofile,
										struct ranlib *ranlib,
										uint64_t index)
{
	uint64_t	i;

	i = 0;
	assert(ofile->ranlibs && index < ofile->nran);
	while (i < index)
	{
		if (ofile->ranlibs[i].ran_off == ranlib->ran_off)
			return (true);
		i++;
	}
	return (false);
}

static bool		is_ran_off_already_in_ranlibs_64(t_ofile *ofile,
											struct ranlib_64 *ranlib,
											uint64_t index)
{
	uint64_t	i;

	i = 0;
	assert(ofile->ranlibs_64 && index < ofile->nran);
	while (i < index)
	{
		if (ofile->ranlibs_64[i].ran_off == ranlib->ran_off)
			return (true);
		i++;
	}
	return (false);
}

static uint64_t	read_archive_nmembers_32(t_ofile *ofile)
{
	uint64_t		nmembers;
	uint64_t		i;

	nmembers = ofile->nran;
	i = 0;
	while (i < ofile->nran)
	{
		if (is_ran_off_already_in_ranlibs(ofile, ofile->ranlibs + i, i))
			nmembers--;
		i++;
	}
	return (nmembers);
}

static uint64_t	read_archive_nmembers_64(t_ofile *ofile)
{
	uint64_t		nmembers;
	uint64_t		i;

	nmembers = ofile->nran;
	i = 0;
	while (i < ofile->nran)
	{
		if (is_ran_off_already_in_ranlibs_64(ofile, ofile->ranlibs_64 + i, i))
			nmembers--;
		i++;
	}
	return (nmembers);
}

uint64_t		read_archive_nmembers(t_ofile *ofile)
{
	assert(ofile->ranlibs || ofile->ranlibs_64);
	if (ofile->ranlibs)
		return (read_archive_nmembers_32(ofile));
	else
		return (read_archive_nmembers_64(ofile));
}
