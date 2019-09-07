#
# LIB MACH O UTILS
#

# Lib
LIB_SRC=src/lib/find_common_indexes.c \
		src/lib/find_load_command_by_command.c \
		src/lib/cpu_type_name.c \
		src/lib/is_valid_cmd.c \
		src/lib/is_valid_flag.c \
		src/lib/is_valid_macho_filetype.c \
		src/lib/is_valid_segment_command_flag.c \
		src/lib/is_valid_symbol_type.c \
		src/lib/load_macho_file.c \
		src/lib/mach_o_error.c \
		src/lib/endian.c \
		src/lib/map_loading_file.c \
		src/lib/check_file_size.c \
		src/lib/check_file_size.c \
		src/lib/read_segments_32.c \
		src/lib/read_segments_64.c

# Archive
LIB_SRC+=src/lib/archive/check_archive_size.c \
		src/lib/archive/get_archive_member_starting_addr.c \
		src/lib/archive/load_archive_file.c \
		src/lib/archive/read_archive_header_members.c \
		src/lib/archive/read_archive_member_name.c \
		src/lib/archive/read_archive_nmembers.c \
		src/lib/archive/read_archive_symdef.c \
		src/lib/archive/load_archive_nth_member.c

# Fat Archive
LIB_SRC+=src/lib/fat_archive/load_fat_archive_file.c \
		src/lib/fat_archive/find_fat_archive_architecture.c \
		src/lib/fat_archive/load_fat_archive_nth_arch.c

# Object
LIB_SRC+=src/lib/object/check_mach_header_integrity.c \
		src/lib/object/read_object_endian.c \
		src/lib/object/read_object_header.c \
		src/lib/object/load_object_file.c \
		src/lib/object/read_object_load_commands.c \
		src/lib/object/check_lc_segment_64_integrity.c \
		src/lib/object/check_lc_segment_integrity.c \
		src/lib/object/check_object_integrity.c \
		src/lib/object/check_lc_symtab_integrity.c

# Swap
LIB_SRC+=src/lib/endian_swap/swap_section.c \
		src/lib/endian_swap/swap_fat_archive_headers.c \
		src/lib/endian_swap/swap_load_command_segment.c \
		src/lib/endian_swap/swap_symtab.c \
		src/lib/endian_swap/swap_object_header.c \
		src/lib/endian_swap/swap_all_load_command.c \
		src/lib/endian_swap/swap_int.c \
		src/lib/endian_swap/swap_load_command_symseg.c \
		src/lib/endian_swap/swap_load_command_symtab.c

# Utils
LIB_SRC+=src/lib/utils/ato16u.c \
		src/lib/utils/ato16u_base.c \
		src/lib/utils/ato64.c

LIB_OBJ=$(LIB_SRC:.c=.o)