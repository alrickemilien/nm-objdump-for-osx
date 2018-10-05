#ifndef MACH_O_UTILS_H
#define MACH_O_UTILS_H

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include "libft.h"

/*
** Here are the magic numbers of an object file
*/

# define STATIC_LIB_MAGIC "!<arch>\x0a"
# define LONG_ARCHIVE_NAME_MAGIC "#1/"

/*
** All needs for endians
*/

typedef enum				e_endian_byte
{
	UNKNOWN_BYTE,
	LITTLE_ENDIAN_BYTE,
	BIG_ENDIAN_BYTE,
}                   t_endian_byte;

/*
** List all .o files types
*/
typedef enum				e_mach_o_file_type
{
	MACH_O_FILE_UNKNOWN,
	MACH_O_FILE_ARCHIVE,
	MACH_O_FILE_FAT,
	MACH_O_FILE_MACHO,
	SUPPORTED_MACH_O_FILE_TYPES,
}                   t_mach_o_file_type;

/*
** Main
*/

void	*map_loading_file(char *filename, uint64_t *file_size);
int		map_unloading_file(void *ptr, uint64_t file_size);

#endif
