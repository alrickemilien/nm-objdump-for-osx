/*
** Check if the field cmd of strcut load_command
** contains a valid value
*/

#include "mach_o_utils.h"

/*
** List all handled cmd type
*/

static const uint32_t g_cmd_map[] = {
	LC_SEGMENT,     /* segment of this file to be mapped */
	LC_SYMTAB,     /* link-edit stab symbol table info */
	LC_SYMSEG,     /* link-edit gdb symbol table info (obsolete) */
	LC_THREAD,     /* thread */
	LC_UNIXTHREAD,     /* unix thread (includes a stack) */
	LC_LOADFVMLIB,     /* load a specified fixed VM shared library */
	LC_IDFVMLIB,     /* fixed VM shared library identification */
	LC_IDENT,     /* object identification info (obsolete) */
	LC_FVMFILE,     /* fixed VM file inclusion (internal use) */
	LC_PREPAGE,     /* prepage command (internal use) */
	LC_DYSYMTAB,     /* dynamic link-edit symbol table info */
	LC_LOAD_DYLIB,     /* load a dynamically linked shared library */
	LC_ID_DYLIB,     /* dynamically linked shared lib ident */
	LC_LOAD_DYLINKER,    /* load a dynamic linker */
	LC_ID_DYLINKER,/* dynamic linker identification */
	LC_PREBOUND_DYLIB,  /* modules prebound for a dynamically */
                                /*  linked shared library */
	LC_ROUTINES,    /* image routines */
	LC_SUB_FRAMEWORK,   /* sub framework */
	LC_SUB_UMBRELLA,    /* sub umbrella */
	LC_SUB_CLIENT,    /* sub client */
	LC_SUB_LIBRARY,    /* sub library */
	LC_TWOLEVEL_HINTS,  /* two-level namespace lookup hints */
	LC_PREBIND_CKSUM,  /* prebind checksum */

	(uint32_t)-1,
};

bool is_valid_cmd(uint32_t cmd)
{
	int	i;

	i = 0;
	while (g_cmd_map[i] != (uint32_t)-1)
	{
		if (g_cmd_map[i] == cmd)
			return (true);
		i++;
	}

	return (false);
}

/*
** From loader.h
** "The cmdsize for 32-bit architectures
** MUST be a multiple of 4 bytes and for 64-bit architectures MUST be a multiple
** of 8 bytes (these are forever the maximum alignment of any load commands).
** The padded bytes must be zero."
*/

bool is_valid_cmdsize(uint32_t cmdsize, uint32_t magic_number)
{
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		if (cmdsize % 0xFF == 0)
			return (true);
	}

	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		if (cmdsize % 0x0F == 0)
			return (true);
	}

	return (false);
}