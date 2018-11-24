#include "mach_o_utils.h"

/*
** List all handled filetype
** Use the macro from loader.h
** relocatable object file
** demand paged executable file
** fixed VM shared library file
** core file
** preloaded executable file
** dynamically bound shared library
** dynamic link editor
** dynamically bound bundle file
** shared library stub for static
** companion file with only debug
** x86_64 kexts
*/

static const uint32_t g_filetype_map[] = {
	MH_OBJECT,
	MH_EXECUTE,
	MH_FVMLIB,
	MH_CORE,
	MH_PRELOAD,
	MH_DYLIB,
	MH_DYLINKER,
	MH_BUNDLE,
	MH_DYLIB_STUB,
                                        /*  linking only, no section contents */
	MH_DSYM,
                                        /*  sections */
	MH_KEXT_BUNDLE,
	(uint32_t)-1,
};

bool is_valid_filetype(uint32_t filetype)
{
	int	i;

	i = 0;
	while (g_filetype_map[i] != (uint32_t)-1)
	{
		if (g_filetype_map[i] == filetype)
			return (true);
		i++;
	}

	return (false);
}