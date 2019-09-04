#
# LIB MACH O UTILS
#

# Lib
LIB_SRC=src/lib/find_common_indexes.c \
		src/lib/find_load_command_by_command.c \
		src/lib/get_cpu_name.c \
		src/lib/is_valid_cmd.c \
		src/lib/is_valid_flag.c \
		src/lib/is_valid_macho_filetype.c \
		src/lib/is_valid_segment_command_flag.c \
		src/lib/is_valid_symbol_type.c \
		src/lib/load_macho_file.c \
		src/lib/mach_o_error.c \
		src/lib/map_loading_file.c \
		src/lib/read_file_type.c

# Archive
LIB_SRC+=src/lib/archive//check_archive_size.c \
		src/lib/archive//get_archive_member_starting_addr.c \
		src/lib/archive//load_archive_file.c \
		src/lib/archive//read_archive_header_members.c \
		src/lib/archive//read_archive_member_name.c \
		src/lib/archive//read_archive_nmembers.c \
		src/lib/archive//read_archive_symdef.c \
		src/lib/archive//read_nth_object_from_archive.c

# Utils
LIB_SRC+=src/lib/utils/ato16u.c \
		src/lib/utils/ato16u_base.c \
		src/lib/utils/ato64.c

LIB_OBJ=$(LIB_SRC:.c=.o)