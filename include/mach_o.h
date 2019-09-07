#ifndef mach_o_H
#define mach_o_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>

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

typedef struct				s_archive_member_header
{
	uint8_t		*member_name;
	int64_t		name_length;
	uint8_t		*st_time;
	off_t		st_size;
	uid_t		st_uid;
	gid_t		st_gid;
	mode_t		st_mode;
	bool		long_name;
	uint8_t		pad[5];
}							t_member_header;

/*
** This structure is used to manipulate mach o files
*/

typedef struct 			s_mach_o {
	// Path to the file
	char				*path;
	uint64_t			file_size;
	uint32_t			type;
	uint32_t			arch_type;

	// Adresse o map loaded file into memory
	void				*addr;
	
	uint32_t			magic;
	uint32_t			endian;

	// Archive
	uint64_t			archive_size;
	void				*archive_start_addr;
	void				*archive_member_header_addr;
	t_member_header		archive_member_header;
	void				*symdef_addr;
	void				*members;
	struct ranlib		*ranlibs;
	struct ranlib_64	*ranlibs_64;
	uint64_t			nran;
	uint64_t			nmembers;
	char				*string_table;
	uint64_t			string_table_size;

	uint32_t				narch;

	// Fat archives
	struct fat_header	*fat_header;
	struct fat_arch		*fat_archs;
	struct fat_arch_64	*fat_archs_64;

	// Mach O object
	void					*o_addr;
	uint64_t				o_size;
	bool					must_be_swapped;
	uint8_t					pad[3];
	struct mach_header		*mh;
	struct mach_header_64	*mh_64;
	struct load_command		*load_commands;
}						t_mach_o;

typedef struct	s_mach_o_processor
{
	uint32_t					nsects;
	uint32_t					nsegs;
	struct section				**secs;
	struct section_64			**secs_64;
	struct segment_command_64	**segs_64;
	struct segment_command		**segs;

	struct symtab_command		*st_lc;
	struct nlist				*symtab;
	struct nlist_64				*symtab_64;
	uint8_t						*string_table;

	struct dysymtab_command		*dysym_lc;

	uint32_t					text_nsect;
	uint32_t					data_nsect;
	uint32_t					bss_nsect;
	uint8_t						pad[4];
}				t_mach_o_processor;

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
** Parsing/Reading functions
*/

int						load_macho_file(
	t_mach_o *ofile,
	char *path,
	void *addr,
	uint64_t file_size);

/*
** Parsing/Reading functions / Archive
*/

int32_t					read_archive_header_members(t_mach_o *file);
int32_t					read_archive_member_name(t_mach_o *file);
int32_t					read_archive_symdef(t_mach_o *file);
uint64_t				read_archive_nmembers(t_mach_o *file);

/*
** Accessors
*/
void				*get_archive_member_starting_addr(t_mach_o *file);
struct load_command	*find_load_command_by_command(
	t_mach_o *mach_o,
	uint32_t cmd);
/*
** Integrity checks
*/

int32_t	check_file_addr_size(t_mach_o *ofile,
								void *addr,
								uint64_t size);
int32_t	check_file_addr(t_mach_o *ofile, void *addr);

int32_t	check_archive_addr_size(t_mach_o *ofile,
								void *addr,
								uint64_t size);
int32_t	check_archive_addr(t_mach_o *ofile, void *addr);

/*
** Utils
*/
uint16_t	ato16u(const char *str);
uint16_t		ato16u_base(
	const char *str,
	const char *base);
int64_t		ato64(const char *str);

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

# define MACH_O_ERROR_INVALID_SYMDEF 9
# define MACH_O_ERROR_INVALID_SYMDEF_STR "First member of archive file is not SYMDEF or SYMDEF_SORTED"

# define MACH_O_ERROR_HEADER_TRUNCATED 10
# define MACH_O_ERROR_HEADER_TRUNCATED_STR "Malformed fat file : the fat header extends past the file"

#endif
