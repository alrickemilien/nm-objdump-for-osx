#ifndef OTOOL_OPTIONS
#define OTOOL_OPTIONS

/*
** All parameter
*/

enum {
	PRINT_FAT_HEADER = 0U,
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

typedef struct s_options {
	int PRINT_FAT_HEADER;

	int	end_index;
	int	file_count;
} t_options;

# pragma pack(pop)

/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
** waiting_for_value: is option waiting for argument
*/

typedef struct 	s_options_map {
	char		*name;
	int			offset;
	int 		(*waiting_for_value)(t_options *options, const char *value);
}				t_options_map;

/*
** Options utils
*/

bool is_a_multi_option(const char *name);
bool is_a_single_option(const char *name);
bool is_a_end_arguments_string(const char *name);
bool is_an_option(const char *name);
bool is_a_waiting_value_option(const char *name);

int read_options_arguments(int ac, char **av, t_options *opt);

/*
** Options with specifc values to handle
*/

#endif
