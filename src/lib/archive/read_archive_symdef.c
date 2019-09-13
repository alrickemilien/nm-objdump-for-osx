#include "mach_o.h"

static bool	is_symdef_32(const t_mach_o *file)
{
	return (ft_strncmp((const char *)file->archive_member_header.member_name,
				SYMDEF,
				sizeof(SYMDEF))
		|| ft_strncmp((const char *)file->archive_member_header.member_name,
				SYMDEF_SORTED,
				sizeof(SYMDEF_SORTED)));
}

static bool	is_symdef_64(const t_mach_o *file)
{
	return (
		ft_strncmp((const char *)file->archive_member_header.member_name,
			SYMDEF_64,
			sizeof(SYMDEF_64))
		|| ft_strncmp((const char *)file->archive_member_header.member_name,
			SYMDEF_64_SORTED,
			sizeof(SYMDEF_64_SORTED)));
}

static void	read_archive_symdef_32(t_mach_o *file)
{
	file->ranlibs = get_archive_member_starting_addr(file);

	file->nran = *(uint32_t*)(void *)file->ranlibs / sizeof(struct ranlib);
	
	file->ranlibs = (void *)((uint8_t*)file->ranlibs + 4);
	
	file->string_table_size = (uint64_t)*(uint32_t *)(void *)(
		(uint8_t *)file->ranlibs + file->nran * sizeof(struct ranlib));
	
	file->string_table = (char *)((uint8_t *)file->ranlibs
					+ file->nran * sizeof(struct ranlib) + sizeof(uint32_t));
	
	file->nmembers = read_archive_nmembers(file);
}

static void	read_archive_symdef_64(t_mach_o *file)
{
	file->ranlibs_64 = get_archive_member_starting_addr(file);
	
	file->nran = *(uint64_t*)(void *)file->ranlibs_64
									/ sizeof(struct ranlib_64);
	file->ranlibs_64 = (void *)((uint8_t*)file->ranlibs + 8);
	
	file->string_table_size = *(uint64_t *)(void *)(
		(uint8_t *)file->ranlibs_64 + file->nran * sizeof(struct ranlib_64));
	
	file->string_table = (char *)((uint8_t *)file->ranlibs_64
				+ file->nran * sizeof(struct ranlib_64) + sizeof(uint64_t));
	
	file->nmembers = read_archive_nmembers(file);
}

int32_t				read_archive_symdef(t_mach_o *file)
{
	file->symdef_addr = file->archive_member_header_addr;
	if (is_symdef_32(file))
	{
		read_archive_symdef_32(file);
	}
	else if (is_symdef_64(file))
	{
		read_archive_symdef_64(file);
	}
	else
	{
		return (mach_o_error(-1, "Invalid symdef for file %s", file->path));
	}
	
	return (0);
}