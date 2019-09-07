#include "mach_o.h"

void	swap_object_header(t_mach_o *file)
{
	struct mach_header	*mh;

	mh = file->mh;
	if (!file->mh) 
		mh = (struct mach_header *)file->mh_64;
	
	assert(mh);
	
	mh->cputype = (cpu_type_t)swap_int32((uint32_t)mh->cputype);
	mh->cpusubtype = (cpu_subtype_t)swap_int32((uint32_t)mh->cpusubtype);
	mh->filetype = swap_int32(mh->filetype);
	mh->ncmds = swap_int32(mh->ncmds);
	mh->sizeofcmds = swap_int32(mh->sizeofcmds);
	mh->flags = swap_int32(mh->flags);
}