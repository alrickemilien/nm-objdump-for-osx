#ifndef OTOOL_H
#define OTOOL_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <unistd.h>

# include "libft.h"
# include "mach_o_utils.h"


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

# define USAGE "./ft_otool <object file>"

# define ERROR_DUMMY_FILE "the file was not recognized"
# define ERROR_UNKNOWN_FILE_FORMAT DUMMY_FILE " as a valid object file\n"
# define ERROR_FAT_DEF "Malformed fat file, "
# define ERROR_FAT_HDR_TRUNC ERR_FAT_DEF "the fat header extends past the file\n"

#endif
