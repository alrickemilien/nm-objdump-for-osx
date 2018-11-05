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
** MACH O HEADER
*/

typedef union                       u_mach_o_header {
              struct mach_header_64 header_64;
              struct mach_header    header;
}                                   t_mach_o_header;

/*
** MACH_O_SECTION
*/

typedef union         u_mach_o_section {
  struct section      section;
  struct section_64   section_64;
}                     t_mach_o_section;

typedef struct        s_mach_o_command {
  struct load_command lc;
  t_mach_o_section    section;
}                     t_mach_o_command;

/*
** Macho o builder structure
*/

typedef struct       s_mach_o_builder {
    t_mach_o_header     header;
    t_list              *cmd; // List of t_mach_o_command
}                    t_mach_o_builder;

/*
** Main
*/

int build_mach_o_from_conf(t_mach_o_builder *builder, const char *path);
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
