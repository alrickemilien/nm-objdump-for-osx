
#
# MACH O BUILDER
#

MACHO_O_BUILDER=mach-o-builder
MACHO_O_BUILDER_SRC=src/mach_o_builder/main.c \
										src/mach_o_builder/read_options_arguments.c \
										src/mach_o_builder/generate_file.c \
										src/mach_o_builder/parser.c \
										src/mach_o_builder/atoi_base.c \
										src/mach_o_builder/load_file.c \
										src/mach_o_builder/mach_o_builder.c \
										src/mach_o_builder/mach_o_builder_buffer_size.c \
										src/mach_o_builder/parser_utils.c
MACHO_O_BUILDER_OBJ=$(MACHO_O_BUILDER_SRC:.c=.o)