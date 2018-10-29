#ifndef MACH_O_BUILDER_OPTIONS_H
#define MACH_O_BUILDER_OPTIONS_H

/*
** Number of handled parameters
*/

#define OPTIONS_MAP_LENGTH 1

enum {
	OUTPUT_FILE = 0,
};


/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
*/

typedef struct 	s_options_map {
	char		*name;
	int			offset;
}				t_options_map;

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

typedef struct s_options {
	int output_file;
} t_options;

int read_options_arguments(int ac, const char **av, t_options *opt);
void print_error_on_option(const char *msg, const char *option);

#endif
