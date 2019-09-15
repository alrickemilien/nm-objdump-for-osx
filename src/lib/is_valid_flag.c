/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:07:41 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 13:07:43 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mach_o.h"

/*
** List all handled flags
** MH_NOUNDEFS,
**	the object file has no undefined
**	   references
**	MH_INCRLINK,
**	the object file is the output of an
**	   incremental link against a base file
**	   and can't be link edited again
**	MH_DYLDLINK,
**	the object file is input for the
**	   dynamic linker and can't be staticly
**	   link edited again
**	MH_BINDATLOAD,
**	the object file's undefined
**	   references are bound by the dynamic
**	   linker when loaded.
**	MH_PREBOUND,
**	the file has its dynamic undefined
**	   references prebound.
**	MH_SPLIT_SEGS,
**	the file has its read-only and
**	   read-write segments split
**	MH_LAZY_INIT,
**	the shared library init routine is
**	   to be run lazily via catching memory
**	   faults to its writeable segments
**	   (obsolete)
**	MH_TWOLEVEL,
**	the image is using two-level name
**	   space bindings
**	MH_FORCE_FLAT,
**	the executable is forcing all images
**	   to use flat name space bindings
**	MH_NOMULTIDEFS,
**	this umbrella guarantees no multiple
**	   defintions of symbols in its
**	   sub-images so the two-level namespace
**	   hints can always be used.
**	MH_NOFIXPREBINDING,
**	 do not have dyld notify the
**	   prebinding agent about this
**	   executable
**	MH_PREBINDABLE,
**	 the binary is not prebound but can
**	   have its prebinding redone. only used
**	   when MH_PREBOUND is not set.
**	MH_ALLMODSBOUND,
**	 indicates that this binary binds to
**	   all two-level namespace modules of
**	   when MH_PREBINDABLE and MH_TWOLEVEL
**	   are both set.
**	MH_SUBSECTIONS_VIA_SYMBOLS,
**	 safe to divide up the sections into
**	   sub-sections via symbols for dead
**	   code stripping
**	MH_CANONICAL,
**	 the binary has been canonicalized
**	   via the unprebind operation
**	MH_WEAK_DEFINES ,
**	 the final linked image contains
**	   external weak symbols
**	MH_BINDS_TO_WEAK ,
**	 the final linked image uses
**	   weak symbols
**
**	MH_ALLOW_STACK_EXECUTION,
**	 When this bit is set, all stacks
**	   in the task will be given stack
**	   execution privilege.  Only used in
**	   MH_EXECUTE filetypes.
**	MH_ROOT_SAFE,
**	 When this bit is set, the binary
**	   declares it is safe for use in
**	   processes with uid zero
**
**	MH_SETUID_SAFE,
**	 When this bit is set, the binary
**	   declares it is safe for use in
**	   processes when issetugid() is true
**
**	MH_NO_REEXPORTED_DYLIBS,
**	 When this bit is set on a dylib,
**	   the static linker does not need to
**	   examine dependent dylibs to see
**	   if any are re-exported
**	MH_PIE,
**	 When this bit is set, the OS will
**	   load the main executable at a
**	   random address.  Only used in
**	   MH_EXECUTE filetypes.
**
**	MH_DEAD_STRIPPABLE_DYLIB,
**	 Only for use on dylibs.  When
**	   linking against a dylib that
**	   has this bit set, the static linker
**	   will automatically not create a
**	   LC_LOAD_DYLIB load command to the
**	   dylib if no symbols are being
**	   referenced from the dylib.
**	MH_HAS_TLV_DESCRIPTORS,
**	 Contains a section of type
**	   S_THREAD_LOCAL_VARIABLES
**
**	MH_NO_HEAP_EXECUTION,
**	 When this bit is set, the OS will
**	   run the main executable with
**	   a non-executable heap even on
**	   platforms (e.g. i386) that don't
**	   require it. Only used in MH_EXECUTE
**	   filetypes.
**
**	MH_APP_EXTENSION_SAFE,
**	 The code was linked for use in an
**	   application extension.
**
** #ifdef MH_NLIST_OUTOFSYNC_WITH_DYLDINFO
**	MH_NLIST_OUTOFSYNC_WITH_DYLDINFO,
**#endif
**	 The external symbols listed in the nlist
**	   symbol table do not include all the symbols
**	   listed in the dyld info.
*/

static const uint32_t g_flag_map[] = {
	MH_NOUNDEFS,
	MH_INCRLINK,
	MH_DYLDLINK,
	MH_BINDATLOAD,
	MH_PREBOUND,
	MH_SPLIT_SEGS,
	MH_LAZY_INIT,
	MH_TWOLEVEL,
	MH_FORCE_FLAT,
	MH_NOMULTIDEFS,
	MH_NOFIXPREBINDING,
	MH_PREBINDABLE,
	MH_ALLMODSBOUND,
	MH_SUBSECTIONS_VIA_SYMBOLS,
	MH_CANONICAL,
	MH_WEAK_DEFINES,
	MH_BINDS_TO_WEAK,
	MH_ALLOW_STACK_EXECUTION,
	MH_ROOT_SAFE,
	MH_SETUID_SAFE,
	MH_NO_REEXPORTED_DYLIBS,
	MH_PIE,
	MH_DEAD_STRIPPABLE_DYLIB,
	MH_HAS_TLV_DESCRIPTORS,
	MH_NO_HEAP_EXECUTION,
	MH_APP_EXTENSION_SAFE,
	MH_NLIST_OUTOFSYNC_WITH_DYLDINFO,
	(uint32_t)-1,
};

bool					is_valid_flag(
	uint32_t flag)
{
	int	i;

	i = 0;
	while (g_flag_map[i] != (uint32_t)-1)
	{
		if (g_flag_map[i] == flag)
			return (true);
		i++;
	}
	return (false);
}
