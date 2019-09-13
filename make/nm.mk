#
# NM
#

NM=ft_nm

NM_SRC=src/nm/main.c \
	src/nm/nm.c \
	src/nm/nm_fat_archive.c \
	src/nm/nm_archive.c \
	src/nm/nm_object.c \
	src/nm/find_section.c \
	src/nm/print_symbol.c \
	src/nm/read_symbols.c \
	src/nm/print_symbol_hex_dump.c \
	src/nm/sort.c \
	src/nm/sort_symbols.c

# Symbols
NM_SRC+=src/nm/symbols/is_symbol_absolute.c \
	src/nm/symbols/is_symbol_arbitrary_sect.c \
	src/nm/symbols/is_symbol_bss.c \
	src/nm/symbols/is_symbol_common.c \
	src/nm/symbols/is_symbol_data.c \
	src/nm/symbols/is_symbol_extern.c \
	src/nm/symbols/is_symbol_extern_absolute.c \
	src/nm/symbols/is_symbol_extern_arbitrary_sect.c \
	src/nm/symbols/is_symbol_extern_bss.c \
	src/nm/symbols/is_symbol_extern_data.c \
	src/nm/symbols/is_symbol_extern_indirect.c \
	src/nm/symbols/is_symbol_extern_text.c \
	src/nm/symbols/is_symbol_extern_unknown.c \
	src/nm/symbols/is_symbol_indirect.c \
	src/nm/symbols/is_symbol_local.c \
	src/nm/symbols/is_symbol_stab.c \
	src/nm/symbols/is_symbol_text.c \
	src/nm/symbols/is_symbol_unknown.c

# Options
NM_SRC+=src/nm/options/read_options_arguments.c \
	src/nm/options/help.c \
	src/nm/options/utils.c \
	src/nm/options/read_arch_option.c \
	src/nm/options/read_radix_option.c

NM_OBJ=$(NM_SRC:.c=.o)