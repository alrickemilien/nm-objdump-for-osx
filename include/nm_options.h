/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_options.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:41:38 by aemilien          #+#    #+#             */
/*   Updated: 2019/09/15 16:55:23 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OPTIONS_H
# define NM_OPTIONS_H

/*
** All parameter
*/

enum {
	ALL_SYMBOL = 0U,
	ONLY_GLOBAL_SYMBOL,
	SORT_NUMERIC,
	PREPEND_FILE_ARCHIVE_NAME,
	ONLY_UNDEFINED_SYMBOL,
	DO_NOT_DISPLAY_UNDEFINED_SYMBOL,
	DISPLAY_NSECT,
	DISPLAY_HEXA,
	ONLY_SYMBOL_NAME,
	LIST_PSEUDO_SYMBOL,
	DISPLAY_DYNAMIC_LIB_SYMBOL,
	DISPLAY_PATH_NAME,
	DISPLAY_PORTABLE,
	ONLY_DYNAMIC,
	ARCH_TYPE,
	SEGMENT_SECTION,
	PRINT_SIZE,
	SORT_SIZE,
	DO_NOT_SORT,
	REVERSE_SORT,
	DEFINED_ONLY,
	RADIX,
	HELP,
	POSIX,
	OPTIONS_NUMBER,
};

/*
** MAximum value of <string> allowed for --opt=<string> or --opt <string>
*/

# define MAX_ALLOWED_VALUE_SIZE 215

/*
** Structure filled with options passed to program
** The handled options are currently -l, -R, -a, -r et -t
** None ls option used in the code :
** print_dir_name : print the dir name in some case at top of list
** At the end stor tty infos
** !! WARNING !!
** Options in struct s_options must be in the same order
** that the enum
*/

# pragma pack(push, 1)

typedef struct	s_options {
	int			all_symbol;
	int			only_global_symbol;
	int			sort_numeric;
	int			prepend_file_archive_name;
	int			only_undefined_symbol;
	int			do_not_display_undefined_symbols;
	int			display_nsect;
	int			display_hexa;
	int			only_symbol_name;
	int			list_pseudo_symbol;
	int			display_dynamic_lib_symbol;
	int			display_path_name;
	int			display_portable;
	int			only_dynamic;
	int			arch_type;
	int			segment_section;
	int			print_size;
	int			sort_size;
	int			do_not_sort;
	int			reverse_sort;
	int			defined_only;
	int			radix;
	int			help;
	int			posix;
	int			end_index;
	int			file_count;
}				t_options;

# pragma pack(pop)

/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
** waiting_for_value: is option waiting for argument
*/

typedef struct	s_options_map {
	char		*name;
	int			offset;
	int			(*waiting_for_value)(
				t_options *options,
				const char *value);
}				t_options_map;

/*
** Options utils
*/

bool			is_a_multi_option(const char *name);
bool			is_a_single_option(const char *name);
bool			is_a_end_arguments_string(const char *name);
bool			is_an_option(const char *name);
bool			is_a_waiting_value_option(const char *name);

int				read_options_arguments(
	int ac, char **av, t_options *opt);

/*
** Options with specifc values to handle
*/

typedef struct	s_arch_option {
	char		*name;
	int			value;
}				t_arch_option;

typedef struct	s_radix_option {
	char		*name;
	int			value;
}				t_radix_option;

int				read_arch_option(
	t_options *options, const char *value);
int				read_radix_option(
	t_options *options, const char *value);

#endif
