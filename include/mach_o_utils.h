#ifndef MACH_O_UTILS_H
#define MACH_O_UTILS_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>

# include "libft.h"

/*
** Here are the magic numbers of an object file
*/

# define STATIC_LIB_MAGIC "!<arch>\x0a"
# define LONG_ARCHIVE_NAME_MAGIC "#1/"

/*
** List all .o files types
*/
typedef enum				e_mach_o_file_type
{
	MACH_O_FILE_UNKNOWN = 0,
	MACH_O_FILE_ARCHIVE,
	MACH_O_FILE_FAT,
	MACH_O_FILE_MACHO,
	SUPPORTED_MACH_O_FILE_TYPES,
}                   t_mach_o_file_type;

/*
** Main
*/

void						*map_loading_file(char *filename, uint64_t *file_size);
int							map_unloading_file(void *ptr, uint64_t file_size);

/*
** MACH O ERROR
*/

typedef struct	s_mach_o_error {
								int	 code;
								char *error;
}								t_mach_o_error;

/*
** Error functionnalities
*/
int							mach_o_error(int code);

/*
** List eqch error of parsing a macho file
*/

# define MACH_O_ERROR_INVALID_MAGICK 0
# define MACH_O_ERROR_INVALID_MAGICK_STR "Invalid magick number"

# define MACH_O_ERROR_INVALID_FILE_SIZE 1
# define MACH_O_ERROR_INVALID_FILE_SIZE_STR "Invalid file size"

# define MACH_O_ERROR_INVALID_FILE_TYPE 2
# define MACH_O_ERROR_INVALID_FILE_TYPE_STR "Invalid file type, should be regular file or link on regulat file"

# define MACH_O_ERROR_MAP_LOADING 3
# define MACH_O_ERROR_MAP_LOADING_STR "File does not exist or permission denied"

# define MACH_O_ERROR_INVALID_MACH_HEADER 4
# define MACH_O_ERROR_INVALID_MACH_HEADER_STR "Invalid mach header"

#endif
