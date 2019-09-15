#ifndef NM_H
# define NM_H

# include <stdio.h>
# include "mach_o.h"
# include "nm_options.h"
# include "libft.h"

# define INTADDR(x) ((void*)(intptr_t)(x))
# define NM_DEFAULT_MACHO_ERROR "%s The file was not recognized as a valid object file\n\n"
# define SUPPORTED_NM_CHAR_SYMBOL_NBR 17
# define NCHARS_SYMBOLS SUPPORTED_NM_CHAR_SYMBOL_NBR
# define BAD_STRING_INDEX "bad string index"

# define NM_EACCESS "%s: Permission denied.\n"
# define NM_EAGAIN "%s: Resource temporarily unavailable.\n"
# define NM_NO_SUCH_FILE "%s: No such file or directory.\n"

typedef struct		s_symbol
{
	struct nlist_64	sym_entry;
	uint8_t			*string;
	uint32_t		len;
	uint32_t		pad;
}					t_symbol;

void				*map_loading_file(
	const char *filename, uint64_t *file_size);
int					map_unloading_file(
	void *ptr, uint64_t file_size);

/*
** Symbol Predicates
*/

typedef struct		s_print_symbol_predicate
{
	bool			(*predicate)(
							t_symbol *symbol,
							t_mach_o_processor *info);
	uint8_t			c;
}					t_print_symbol_predicate;

int					read_options_arguments(
	int ac, char **av, t_options *options);
int					nm(
	t_options *options, const char *path);
int32_t				nm_object(t_mach_o *file, t_options *options);
int32_t				nm_fat_archive(t_mach_o *file, t_options *options);
int32_t				nm_archive(t_mach_o *file, t_options *options);
void				sort_symbols(t_symbol *symbols,
					const uint64_t symbols_number,
					const t_options *options);
t_symbol			*read_symbols(t_mach_o *ofile,
					t_mach_o_processor *info);
void				print_symbol(t_mach_o *file,
					t_symbol *symbol,
					t_mach_o_processor *info,
					t_options *options);
uint32_t			find_section(t_mach_o_processor *info,
					char *seg_name,
					char *sec_name);

void				print_default_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c);
void				print_unknown_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c);
void				print_hex_dump_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info);

/*
** Symbols
*/

bool				is_symbol_absolute(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_arbitrary_sect(t_symbol *symbol,
									t_mach_o_processor *info);
bool				is_symbol_bss(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_common(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_data(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_extern(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_extern_absolute(t_symbol *symbol,
										t_mach_o_processor *info);
bool				is_symbol_extern_arbitrary_sect(t_symbol *symbol,
													t_mach_o_processor *info);
bool				is_symbol_extern_bss(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_extern_data(t_symbol *symbol,
									t_mach_o_processor *info);
bool				is_symbol_extern_indirect(t_symbol *symbol,
										t_mach_o_processor *info);
bool				is_symbol_extern_text(t_symbol *symbol,
									t_mach_o_processor *info);
bool				is_symbol_extern_unknown(t_symbol *symbol,
										t_mach_o_processor *info);
bool				is_symbol_indirect(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_local(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_text(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_stab(
	t_symbol *symbol, t_mach_o_processor *info);
bool				is_symbol_unknown(
	t_symbol *symbol, t_mach_o_processor *info);

/*
** Utils
*/

void				sort(
	void *tab,
	size_t elem_nbr,
	size_t type_size,
	int (*cmp)(const void *, const void *));

int					exit_with_help(void);

# define NOT_RECOGNIZED_VALID_FILE_EXIT_CODE 1

#endif
