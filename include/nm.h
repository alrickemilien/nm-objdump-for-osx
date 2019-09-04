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

/*
** Main
*/

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
