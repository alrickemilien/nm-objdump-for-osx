OS := $(shell uname)

ifneq ($(OS),Darwin)
$(error OSX required ...)
endif

CCFLAGS= -Wall -Wextra -Werror

LIBFT=libft
DIR_LIBFT=libft
LINK_LIBFT=-lft -L $(DIR_LIBFT)

NM=ft_nm
NM_SRC=src/nm/main.c \
			src/nm/read_options_arguments.c \
			src/nm/error.c
NM_OBJ=$(NM_SRC:.c=.o)

OTOOL=ft_otool
OTOOL_SRC=src/otool/main.c
OTOOL_OBJ=$(OTOOL_SRC:.c=.o)

LIB_SRC=src/lib/map_loading_file.c \
				src/lib/mach_o_error.c \
				src/lib/endian.c \
				src/lib/is_valid_filetype.c \
				src/lib/is_valid_flag.c \
				src/lib/is_valid_cmd.c
LIB_OBJ=$(LIB_SRC:.c=.o)

MACHO_O_BUILDER=mach-o-builder
MACHO_O_BUILDER_SRC=src/mach_o_builder/main.c \
										src/mach_o_builder/read_options_arguments.c \
										src/mach_o_builder/generate_file.c \
										src/mach_o_builder/parser.c \
										src/mach_o_builder/atoi_base.c
MACHO_O_BUILDER_OBJ=$(MACHO_O_BUILDER_SRC:.c=.o)

INCLUDE=-I include -I libft

.PHONY: all clean fclean

all: $(NM) $(OTOOL)

$(MACHO_O_BUILDER): $(LIB_OBJ) $(MACHO_O_BUILDER_OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(LINK_LIBFT)

$(NM): $(LIB_OBJ) $(NM_OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(LINK_LIBFT)

$(OTOOL): $(LIB_OBJ) $(OTOOL_OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(LINK_LIBFT)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(NM_OBJ) $(OTOOL_OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(NM) $(OTOOL)

re: fclean all
