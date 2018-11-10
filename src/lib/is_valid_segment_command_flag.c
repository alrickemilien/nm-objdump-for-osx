#include "mach_o_utils.h"

/*
** List all handled segment command flags
**
*/

static const uint32_t g_segment_command_flag_map[] = {
	SG_HIGHVM,
	/* the file contents for this segment is for
	the high part of the VM space, the low part
	is zero filled (for stacks in core files) */
	SG_FVMLIB,
	/* this segment is the VM that is allocated by
	a fixed VM library, for overlap checking in
	the link editor */
	SG_NORELOC,
	/* this segment has nothing that was relocated
	in it and nothing relocated to it, that is
	it maybe safely replaced without relocation*/
	SG_PROTECTED_VERSION_1,
 	/* This segment is protected.  If the
	segment starts at file offset 0, the
	first page of the segment is not
	protected.  All other pages of the
	segment are protected. */

	(uint32_t)-1,
};

bool is_valid_flag(uint32_t flag)
{
	int	i;

	i = 0;
	while (g_segment_command_flag_map[i] != (uint32_t)-1)
	{
		if (g_segment_command_flag_map[i] == flag)
			return (true);
		i++;
	}

	return (false);
}
