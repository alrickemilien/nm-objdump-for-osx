ifneq ($(OS),Darwin)
$(error OSX required ...)
endif

CCFLAGS= -Wall -Wextra -Werror

LIBFT=libft
DIR_LIBFT=libft
LINK_LIBFT=-lft -L $(DIR_LIBFT)

NM=nm
NM_SRC=src/nm/main.c
NM_OBJ=$(NM_SRC:.c=.o)

OTOOL=otool
OTOOL_SRC=src/otool/main.c
OTOOL_OBJ=$(OTOOL_SRC:.c=.o)

INCLUDE=-I include -I libft

.PHONY: all clean fclean

all: $(NM) $(OTOOL)

$(NM): $(NM_OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(INCLUDE) $(LINK_LIBFT)

$(OTOOL): $(OTOOL_OBJ)
	@make -C $(DIR_LIBFT)
	@gcc $^ -o $@ $(INCLUDE) $(LINK_LIBFT)

%.o: %.c
	@gcc -o $@ -c $< $(INCLUDE) $(CCFLAGS)

clean:
	@make clean -C $(DIR_LIBFT)
	@rm -rf $(NM_OBJ) $(OTOOL_OBJ)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@rm -rf $(NM) $(OTOOL)

re: fclean all
