#ifndef OTOOL_H
#define OTOOL_H

# include "libft.h"
# include "mach_o.h"
# include "otool_options.h"

/*
** Main
*/

int                             otool(
                                    t_options *options, const char *path);
int                             otool_object(
                                    t_mach_o *file, t_options *options);
int                             otool_archive(
                                    t_mach_o *file, t_options *options);
int                             otool_fat_archive(
                                    t_mach_o *file, t_options *options);

typedef struct                  s_otool_dump {
	uint32_t					nsects;
	uint32_t					nsegs;
	struct section				**secs;
	struct section_64			**secs_64;
	struct segment_command_64   **segs_64;
	struct segment_command		**segs;
	uint32_t					text_nsec;
}                               t_otool_dump;

/*
** Print
*/

int                             print_section_32(
                                    t_mach_o *file, t_otool_dump *info, uint32_t nsec);
int                             print_section_64(
                                    t_mach_o *file, t_otool_dump *otool_info, uint32_t nsec);

/*
** Exit
*/

int exit_with_help(void);

#endif
