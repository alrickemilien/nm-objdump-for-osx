
#
# NM
#

NM=ft_nm
NM_SRC=src/nm/main.c \
			src/nm/read_options_arguments.c \
			src/nm/error.c
NM_OBJ=$(NM_SRC:.c=.o)