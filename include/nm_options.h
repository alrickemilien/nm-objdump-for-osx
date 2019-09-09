#ifndef NM_OPTIONS
#define NM_OPTIONS

/*
** Number of handled parameters
*/

#define OPTIONS_MAP_LENGTH 15

/*
**  -a     Display all symbol table entries, including those inserted for use by debuggers.
**  -g     Display only global (external) symbols.
**  -n     Sort numerically rather than alphabetically.
**  -o     Prepend file or archive element name to each output line, rather than only once.
**  -p     Don't sort; display in symbol-table order.
**  -r     Sort in reverse order.
**  -u     Display only undefined symbols.
**  -U     Don't display undefined symbols.
**  -m     Display  the  N_SECT  type  symbols (Mach-O symbols) as (segment_name, section_name) followed by either external or non-external and then the symbol
**  						name.  Undefined, common, absolute and indirect symbols get displayed as (undefined), (common), (absolute), and (indirect), respectively.
**  -x     Display the symbol table entry's fields in hexadecimal, along with the name as a string.
**  -j     Just display the symbol names (no value or type).
**  -l     List a pseudo symbol .section_start if no symbol has as its value the starting address of the section.  (This is used with the -s option above.)
**  -f     For nm-classic(1) this displays the symbol table of a dynamic library flat (as one file not separate modules).  This is obsolete and  not  supported
**  			with llvm-nm(1).
**  -A     Write the pathname or library name of an object on each line.
**  -P     Write information in a portable output format.
*/

enum {
	ALL_SYMBOL = 0,
	ONLY_GLOBAL_SYMBOL,
	SORT_NUMERIC,
	PREPEND_FILE_ARCHIVE_NAME,
	DO_NOT_SORT,
	REVERSE_SORT,
	ONLY_UNDEFINED_SYMBOL,
	DO_NOT_DISPLAY_UNDEFINED_SYMBOL,
	DISPLAY_NSECT,
	DISPLAY_HEXA,
	ONLY_SYMBOL_NAME,
	LIST_PSEUDO_SYMBOL,
	DISPLAY_DYNAMIC_LIB_SYMBOL,
	DISPLAY_PATH_NAME,
	DISPLAY_PORTABLE,
};

# define MAX_ALLOWED_VALUE_SIZE 215

/*
** Map used to handle each option :
** name : Char* value
** offset: offset in the structure s_options
*/

typedef struct 	s_options_map {
	char		*name;
	int			offset;
	bool		waiting_for_value;
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
	int x;
	int g;
	int f;
	int j;
	int u;
	int capital_u;
	int p;
	int r;
	int n;
	int help;
} t_options;

int read_options_arguments(int ac, char **av, t_options *opt);

#endif
