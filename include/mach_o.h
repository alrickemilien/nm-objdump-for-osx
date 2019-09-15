/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:39:33 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 12:39:34 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACH_O_H
# define MACH_O_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include "libft.h"

/*
** Here are the magic numbers of an object file
*/

# define STATIC_LIB_MAGIC "!<arch>\x0a"
# define LONG_ARCHIVE_NAME_MAGIC "#1/"
# define MAX_ERROR_BUFFER PATH_MAX + 512

typedef enum					e_endian
{
	UNKNOWN_ENDIAN = 0U,
}								t_endian;

/*
** List all files types handled
** WARNING
** Do not mix file type (archive, fat arch, macho file)
** and macho file type (MH_OBJECT, MH_EXECUTE, MH_FVMLIB)
** specific for macho file header
*/

typedef enum					e_mach_o_file_type
{
	UNKNOWN_FILE = 0U,
	ARCHIVE_FILE,
	FAT_FILE,
	OBJECT_FILE,
	SUPPORTED_FILE_TYPES,
}								t_mach_o_file_type;

typedef struct					s_archive_member_header
{
	uint8_t						*member_name;
	int64_t						name_length;
	uint8_t						*st_time;
	off_t						st_size;
	uid_t						st_uid;
	gid_t						st_gid;
	mode_t						st_mode;
	bool						long_name;
}								t_member_header;

/*
** This structure is used to manipulate mach o files
*/

typedef struct					s_mach_o {
	const char					*path;
	uint64_t					file_size;
	uint32_t					type;
	uint32_t					arch_type;
	void						*addr;
	uint32_t					magic;
	uint32_t					endian;
	uint64_t					archive_size;
	void						*archive_start_addr;
	void						*archive_member_header_addr;
	t_member_header				archive_member_header;
	void						*symdef_addr;
	void						*members;
	struct ranlib				*ranlibs;
	struct ranlib_64			*ranlibs_64;
	uint64_t					nran;
	uint64_t					nmembers;
	char						*string_table;
	uint64_t					string_table_size;
	uint32_t					narch;
	struct fat_header			*fat_header;
	struct fat_arch				*fat_archs;
	struct fat_arch_64			*fat_archs_64;
	void						*o_addr;
	uint64_t					o_size;
	uint64_t					o_endian;
	bool						must_be_swapped;
	struct mach_header			*mh;
	struct mach_header_64		*mh_64;
	struct load_command			*load_commands;
}								t_mach_o;

typedef struct					s_mach_o_processor
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
}								t_mach_o_processor;

/*
** Main
*/

bool							is_valid_filetype(
	uint32_t filetype);
bool							is_valid_flag(
	uint32_t flag);
bool							is_valid_cmd(
	uint32_t cmd);
bool							is_valid_symbol_type(
	uint8_t n_type);

/*
** Parsing/Reading functions
*/

unsigned						read_file_type(
	t_mach_o *file);
int								load_macho_file(
	t_mach_o *ofile,
	const char *path,
	void *addr,
	uint64_t file_size);

/*
** Parsing/Reading functions / Archive
*/

int								load_archive_file(
							t_mach_o *file,
							void *archive_addr,
							uint64_t archive_size);
int								read_header_of_one_archives_member(
	t_mach_o *file);
int								read_archive_member_name(t_mach_o *file);
int								read_archive_symdef(t_mach_o *file);
uint64_t						read_archive_nmembers(t_mach_o *file);
int								load_archive_nth_member(t_mach_o *file,
											uint64_t n_member,
											bool *error);

/*
** Parsing/Reading functions / Fat Archive
*/

int								load_fat_archive_file(
							t_mach_o *file,
							void *archive_addr,
							uint64_t archive_size);
int								find_fat_archive_architecture(
							t_mach_o *file,
							cpu_type_t cputype,
							cpu_subtype_t subtype);
int								load_fat_archive_nth_arch(
							t_mach_o *file,
							uint32_t narch);

/*
** Parsing/Reading functions / Object
*/

int								load_object_file(
								t_mach_o *file,
								void *object_addr,
								uint64_t object_size);
uint32_t						read_object_endian(struct mach_header *header);
void							*read_object_header(t_mach_o *file);
struct load_command				*read_object_load_commands(t_mach_o *file);
int								check_object_integrity(t_mach_o *file);
int								check_object_addr(t_mach_o *file, void *addr);
int								check_object_addr_size(
							t_mach_o *file,
							void *addr,
							uint64_t size);

typedef struct					s_lc_integrity_check
{
	int							(*f)(
		t_mach_o *file, struct load_command *lc);
	uint32_t					cmd;
}								t_lc_integrity_check;

/*
** Accessors
*/

void							*get_archive_member_starting_addr(
	t_mach_o *file);
struct load_command				*find_load_command_by_command(
	t_mach_o *mach_o,
	uint32_t cmd);
struct segment_command_64		**read_segments_64(
	t_mach_o *file,
	uint32_t *return_nsegs);
struct segment_command			**read_segments_32(
	t_mach_o *file,
											uint32_t *return_nsegs);

struct section					**read_sections_32(
	t_mach_o *file,
											uint32_t *return_nsects);

struct section_64				**read_sections_64(
	t_mach_o *file,
											uint32_t *return_nsects);

/*
** Integrity checks
*/

int								check_file_addr_size(t_mach_o *file,
								void *addr,
								uint64_t size);
int								check_file_addr(t_mach_o *file, void *addr);

int								check_archive_addr_size(t_mach_o *file,
								void *addr,
								uint64_t size);
int								check_archive_addr(t_mach_o *file, void *addr);
int								check_mach_header_integrity(t_mach_o *file);
int								check_lc_symtab_integrity(t_mach_o *file,
									struct load_command *lc);
int								check_lc_segment_64_integrity(
	t_mach_o *file, struct load_command *lc);
int								check_lc_segment_integrity(
	t_mach_o *file, struct load_command *lc);

/*
** Swaps utilities
*/

uint16_t						swap_int16(uint16_t v);
uint32_t						swap_int32(uint32_t v);
uint64_t						swap_int64(uint64_t v);
int								swap_all_load_commands(t_mach_o *file);
void							swap_object_header(t_mach_o *file);
void							swap_symtab(t_mach_o *file);
void							swap_section_32(struct section *section);
void							swap_section_64(struct section_64 *section);
void							swap_load_command_segment_32(
	struct load_command *lc);
void							swap_load_command_segment_64(
	struct load_command *lc);
void							swap_load_command_symtab(
	struct load_command *lc);
void							swap_load_command_symseg(
	struct load_command *lc);
int32_t							swap_fat_archive_headers(t_mach_o *file);

typedef struct					s_lc_swapper
{
	void						(*f)(
		struct load_command *lc);
	uint32_t					cmd;
}								t_lc_swapper;

/*
** Utils
*/

uint16_t						ato16u(const char *str);
uint16_t						ato16u_base(
	const char *str,
	const char *base);
int64_t							ato64(const char *str);
uint64_t						endian(void);
const char						*cpu_type_name(cpu_type_t cpu_type);

/*
** MACH O ERROR
*/

typedef struct					s_mach_o_error {
	int							code;
	char						*error;
}								t_mach_o_error;

/*
** Error functionnalities
*/

int								mach_o_error(
	int code, const char *fmt, ...);
void							init_prefix_mach_o_error(
	const char *prefix);
void							set_prefix_mach_o_error_to_buffer(
	char *buffer);
void							init_prefix_error(
	char *argv_0);
#endif
