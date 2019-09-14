#ifndef OTOOL_H
#define OTOOL_H

# include "libft.h"
# include "mach_o.h"
# include "otool_options.h"

/*
** Main
*/

int	otool(t_options *options, const char *path);
int	otool_object(t_mach_o *file, t_options *options);
int	otool_archive(t_mach_o *file, t_options *options);
int	otool_fat_archive(t_mach_o *file, t_options *options);

/*
** Exit
*/

int exit_with_help(void);

#endif
