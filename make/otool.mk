#
# OTOOL
#

OTOOL=ft_otool

OTOOL_SRC=src/otool/otool_fat_archive.c \
			src/otool/main.c \
			src/otool/otool.c \
			src/otool/otool_object.c \
			src/otool/otool_archive.c

# Options
OTOOL_SRC+=src/otool/options/read_options_arguments.c \
			src/otool/options/help.c \
			src/otool/options/utils.c

OTOOL_OBJ=$(OTOOL_SRC:.c=.o)