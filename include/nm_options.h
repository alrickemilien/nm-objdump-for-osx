#ifndef NM_OPTIONS
#define NM_OPTIONS

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
	PRINT_AFTER_ALL,
	PRINT_BEFORE_ALL,
	DEFINED_ONLY,
	RADIX,
	HELP,
	OPTIONS_NUMBER,
};

/*
** MAximum value of <string> allowed for --opt=<string> or --opt <string>
*/

# define MAX_ALLOWED_VALUE_SIZE 215

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
	int ALL_SYMBOL;
	int ONLY_GLOBAL_SYMBOL;
	int SORT_NUMERIC;
	int PREPEND_FILE_ARCHIVE_NAME;
	int ONLY_UNDEFINED_SYMBOL;
	int DO_NOT_DISPLAY_UNDEFINED_SYMBOL;
	int DISPLAY_NSECT;
	int DISPLAY_HEXA;
	int ONLY_SYMBOL_NAME;
	int LIST_PSEUDO_SYMBOL;
	int DISPLAY_DYNAMIC_LIB_SYMBOL;
	int DISPLAY_PATH_NAME;
	int DISPLAY_PORTABLE;
	int ONLY_DYNAMIC;
	int ARCH_TYPE;
	int SEGMENT_SECTION;
	int PRINT_SIZE;
	int SORT_SIZE;
	int DO_NOT_SORT;
	int REVERSE_SORT;
	int PRINT_AFTER_ALL;
	int PRINT_BEFORE_ALL;
	int DEFINED_ONLY;
	int RADIX;
	int HELP;

	int	end_index;
	int	file_count;
} t_options;

# pragma pack(pop)

/*
** Options utils
*/

bool is_a_multi_option(const char *name);
bool is_a_single_option(const char *name);
bool is_a_end_arguments_string(const char *name);
bool is_an_option(const char *name);

int read_options_arguments(int ac, char **av, t_options *opt);

/*
** Options with specifc values to handle
*/

int read_arch_option(t_options *options, const char *value);

#endif
