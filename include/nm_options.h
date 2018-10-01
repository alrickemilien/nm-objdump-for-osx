#ifndef NM_OPTIONS
#define NM_OPTIONS

/**
** Number of handled parameters
*/

#define OPTIONS_MAP_LENGTH 1

enum {
	FOO_OPTION,
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
	int foo_option;
} t_options;

#endif
