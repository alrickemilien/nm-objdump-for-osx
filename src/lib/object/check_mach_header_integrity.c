#include "mach_o.h"

int32_t check_mach_header_integrity(t_mach_o *file)
{
	if (file->mh)
	{
		if (file->mh->sizeofcmds + sizeof(struct mach_header)
			> file->o_size
		|| file->mh->ncmds * sizeof(struct load_command)
			+ sizeof(struct mach_header) > file->o_size)
		{
			dprintf(2, "truncated or malformed object"
				" (load commands extend past the end of the file)\n");
			return (-1);
		}
	}
	else if (file->mh_64)
	{
		if (file->mh_64->sizeofcmds + sizeof(struct mach_header_64)
			> file->o_size
		|| file->mh_64->ncmds * sizeof(struct load_command)
			+ sizeof(struct mach_header_64) > file->o_size)
		{
			dprintf(2, "truncated or malformed object"
				" (load commands extend past the end of the file)\n");
			return (-1);
		}
	}
	return (0);
}