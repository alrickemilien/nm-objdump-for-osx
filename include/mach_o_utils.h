#ifndef MACH_O_UTILS_H
#define MACH_O_UTILS_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

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
** List all files types handled
** WARNING
** Do not mix file type (archive, fat arch, macho file)
** and macho file type (MH_OBJECT, MH_EXECUTE, MH_FVMLIB)
** specific for macho file header
*/

typedef enum				e_mach_o_file_type
{
	MACH_O_FILE_UNKNOWN = 0U,
	ARCHIVE_FILE,
	FAT_FILE,
	OBJECT_FILE,
	SUPPORTED_MACH_O_FILE_TYPES,
}                   t_mach_o_file_type;

/*
** This structure is used to manipulate mach o files
*/

typedef struct	s_mach_o {
	// Path to the file
	char				*path;

	// Adresse o map loaded file into memory
	void				*addr;
	
	t_mach_o_file_type	file_type;
	uint32_t			magic;
	uint32_t			endian;
}								t_mach_o;

/*
** Main
*/

void						*map_loading_file(char *filename, uint64_t *file_size);
int							map_unloading_file(void *ptr, uint64_t file_size);

bool						is_valid_filetype(uint32_t filetype);
bool						is_valid_flag(uint32_t flag);
bool						is_valid_cmd(uint32_t cmd);
bool						is_valid_symbol_type(uint8_t n_type);

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
** List each error of parsing a macho file
*/

# define MACH_O_ERROR_INVALID_MAGICK 0
# define MACH_O_ERROR_INVALID_MAGICK_STR "Invalid magick number"

# define MACH_O_ERROR_INVALID_FILE_SIZE 1
# define MACH_O_ERROR_INVALID_FILE_SIZE_STR "Invalid file size"

# define MACH_O_ERROR_INVALID_FILE 2
# define MACH_O_ERROR_INVALID_FILE_STR "Invalid file type, should be regular file or link on regulat file"

# define MACH_O_ERROR_MAP_LOADING 3
# define MACH_O_ERROR_MAP_LOADING_STR "File does not exist or permission denied"

# define MACH_O_ERROR_INVALID_MACH_HEADER 4
# define MACH_O_ERROR_INVALID_MACH_HEADER_STR "Invalid mach header"

# define MACH_O_ERROR_INVALID_FILETYPE 5
# define MACH_O_ERROR_INVALID_FILETYPE_STR "Invalid file type"

# define MACH_O_ERROR_INVALID_SYMBOL_TYPE 6
# define MACH_O_ERROR_INVALID_SYMBOL_TYPE_STR "Invalid symbol type"

# define MACH_O_ERROR_NO_SECTION_FOUND 7
# define MACH_O_ERROR_NO_SECTION_FOUND_STR "No section found with the given sectname and segname"

# define MACH_O_ERROR_INVALID_FILE_TYPE 8
# define MACH_O_ERROR_INVALID_FILE_TYPE_STR "Unrecognized file type"

#endif
