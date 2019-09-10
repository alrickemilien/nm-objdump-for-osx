OS := $(shell uname)

ifneq ($(OS),Darwin)
$(error OSX required ...)
endif

CCFLAGS= -Wall -Wextra -Werror

BUILD_DIR=build/

LIBFT=libft
DIR_LIBFT=libft
LINK_LIBFT=-lft -L $(DIR_LIBFT)

include make/mach_o.mk
include make/nm.mk
include make/otool.mk
include make/mach_o_builder.mk

INCLUDE=-I include -I libft

.PHONY: all clean fclean

all: $(NM) $(OTOOL) $(MACHO_O_BUILDER)

$(MACHO_O_BUILDER): $(LIB_OBJ) $(MACHO_O_BUILDER_OBJ)
	@make -C $(DIR_LIBFT)
	@mkdir -p $(BUILD_DIR)
	@gcc $^ -o $(BUILD_DIR)$@ $(LINK_LIBFT) $(CCFLAGS)

$(NM): $(LIB_OBJ) $(NM_OBJ)
	@make -C $(DIR_LIBFT)
	@mkdir -p $(BUILD_DIR)
	@gcc $^ -o $(BUILD_DIR)$@ $(LINK_LIBFT) $(CCFLAGS)

$(OTOOL): $(LIB_OBJ) $(OTOOL_OBJ)
	@make -C $(DIR_LIBFT)
	@mkdir -p $(BUILD_DIR)
	@gcc $^ -o $(BUILD_DIR)$@ $(LINK_LIBFT) $(CCFLAGS)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(NM_OBJ) $(OTOOL_OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(NM) $(OTOOL)

re: fclean all
