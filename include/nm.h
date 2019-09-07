#ifndef NM_OTOOL_H
#define NM_OTOOL_H

# include <stdio.h>

# include "mach_o.h"
# include "nm_options.h"
# include "libft.h"

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

int     read_options_arguments(int ac, char **av, t_options *options);
int     nm(t_options *options, const char *path);
int32_t	nm_object(t_mach_o *file, t_options *options);
int32_t nm_fat_archive(t_mach_o *file, t_options *options);
int32_t	nm_archive(t_mach_o *file, t_options *options);
void	sort_symbols(t_symbol *symbols,
					const uint64_t symbols_number,
					const t_options *options);

/*
**   __________________  ___________  ______
** _/ __ \_  __ \_  __ \/  _ \_  __ \/  ___/
** \  ___/|  | \/|  | \(  <_> )  | \/\___ \
**  \___  >__|   |__|   \____/|__|  /____  >
**      \/                               \/
*/

void print_error_on_option(const char *msg, const char *option);

# define USAGE "./ft_nm <object file>"

#endif
