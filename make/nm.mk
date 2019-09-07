
#
# NM
#

NM=ft_nm

NM_SRC=src/nm/main.c \
	src/nm/read_options_arguments.c \
	src/nm/error.c \
	src/nm/nm.c \
	src/nm/nm_fat_archive.c \
	src/nm/nm_archive.c \
	src/nm/nm_object.c

NM_OBJ=$(NM_SRC:.c=.o)