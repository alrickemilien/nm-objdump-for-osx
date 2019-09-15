/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:41:29 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 12:41:30 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "libft.h"
# include "mach_o.h"
# include "otool_options.h"

# define NO_SECT_FOUND ((uint32_t)-1)
# define INTADDR(x) ((void*)(intptr_t)(x))
# define OTOOL_DEFAULT_MACHO_ERROR "%s: is not an object file\n"

void							*map_loading_file(
	const char *filename, uint64_t *file_size);
int								map_unloading_file(
	void *ptr, uint64_t file_size);

typedef struct					s_otool_dump {
	uint32_t					nsects;
	uint32_t					nsegs;
	struct section				**secs;
	struct section_64			**secs_64;
	struct segment_command_64	**segs_64;
	struct segment_command		**segs;
	uint32_t					text_nsec;
}								t_otool_dump;

/*
** Main
*/

int								otool(
	t_options *options, const char *path);
int								otool_object(
	t_mach_o *file, t_options *options);
int								otool_archive(
	t_mach_o *file, t_options *options);
int								otool_fat_archive(
	t_mach_o *file, t_options *options);
uint32_t						find_section(
	t_otool_dump *info,
	char *seg_name,
	char *sec_name);

/*
** Print
*/

int								print_section_32(
	t_mach_o *file, t_otool_dump *info, uint32_t nsec);
int								print_section_64(
	t_mach_o *file, t_otool_dump *otool_info, uint32_t nsec);

/*
** Exit
*/

int								exit_with_help(void);

#endif
