#ifndef NM_OTOOL_H
#define NM_OTOOL_H

# include <stdio.h>

# include "mach_o.h"
# include "nm_options.h"
# include "libft.h"

# define LOGDEBUG(f_, ...) printf((f_), __VA_ARGS__)

/*
** All ok
*/

# define EXIT_OK 0

/*
** If minor problems (e.g., cannot access subdirectory)
*/

# define EXIT_FAILURE 1

typedef struct      s_symbol
{
	struct nlist_64 sym_entry;
	uint8_t         *string;
	uint32_t        len;
	uint32_t		pad;
}                   t_symbol;

/*
** Symbol Predicates
*/

typedef struct	s_print_symbol_predicate
{
	bool				(*predicate)(
							t_symbol *symbol,
							t_mach_o_processor *info);
	uint8_t				c;
}				t_print_symbol_predicate;

# define SUPPORTED_NM_CHAR_SYMBOL_NBR 17
# define NCHARS_SYMBOLS SUPPORTED_NM_CHAR_SYMBOL_NBR
# define BAD_STRING_INDEX "bad string index"

int     	read_options_arguments(int ac, char **av, t_options *options);
int     	nm(t_options *options, const char *path);
int32_t		nm_object(t_mach_o *file, t_options *options);
int32_t 	nm_fat_archive(t_mach_o *file, t_options *options);
int32_t		nm_archive(t_mach_o *file, t_options *options);
void		sort_symbols(t_symbol *symbols,
					const uint64_t symbols_number,
					const t_options *options);
t_symbol	*read_symbols(t_mach_o *ofile,
					t_mach_o_processor *info);
void		print_symbol(t_mach_o *file,
					t_symbol *symbol,
					t_mach_o_processor *info,
					t_options *options);
uint32_t	find_section(t_mach_o_processor *info,
					char *seg_name,
					char *sec_name);

void	print_default_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c);
void	print_undefined_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info,
	char c);
void	print_hex_dump_symbol(
	t_symbol *symbol,
	t_mach_o_processor *info);

/*
** Symbols
*/

bool			is_symbol_absolute(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_arbitrary_sect(t_symbol *symbol,
									t_mach_o_processor *info);
bool			is_symbol_bss(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_common(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_data(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_extern(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_extern_absolute(t_symbol *symbol,
										t_mach_o_processor *info);
bool			is_symbol_extern_arbitrary_sect(t_symbol *symbol,
													t_mach_o_processor *info);
bool			is_symbol_extern_bss(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_extern_data(t_symbol *symbol,
									t_mach_o_processor *info);
bool			is_symbol_extern_indirect(t_symbol *symbol,
										t_mach_o_processor *info);
bool			is_symbol_extern_text(t_symbol *symbol,
									t_mach_o_processor *info);
bool			is_symbol_extern_unknown(t_symbol *symbol,
										t_mach_o_processor *info);
bool			is_symbol_indirect(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_local(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_text(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_stab(t_symbol *symbol, t_mach_o_processor *info);
bool			is_symbol_unknown(t_symbol *symbol, t_mach_o_processor *info);

/*
** Utils
*/
void					sort(
    void *tab,
    size_t elem_nbr,
    size_t type_size,
    int (*cmp)(const void *, const void *));

/*
**   __________________  ___________  ______
** _/ __ \_  __ \_  __ \/  _ \_  __ \/  ___/
** \  ___/|  | \/|  | \(  <_> )  | \/\___ \
**  \___  >__|   |__|   \____/|__|  /____  >
**      \/                               \/
*/

void print_error_on_option(const char *msg, const char *option);

# define USAGE "./ft_nm <object file>"

# define NOT_RECOGNIZED_VALID_FILE_EXIT_CODE 1

#endif
