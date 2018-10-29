#ifndef MACH_O_BUILDER_H
#define MACH_O_BUILDER_H

# include <stdio.h>

# include "mach_o_utils.h"
# include "libft.h"
# include "mach_o_builder_options.h"

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
int build_mach_o_from_conf(const char *path);
int write_buffer_to_file(const char *output);
int load_file_descriptor(const char *path);

/*
**   __________________  ___________  ______
** _/ __ \_  __ \_  __ \/  _ \_  __ \/  ___/
** \  ___/|  | \/|  | \(  <_> )  | \/\___ \
**  \___  >__|   |__|   \____/|__|  /____  >
**      \/                               \/
*/

# define USAGE "./macho-o-builder <object file>"

#endif
