#include "nm.h"

/*
**	nm
*/

void print(uint32_t nsyms, int symoff, int stroff, char *ptr)
{
	uint32_t							i;
	char						*stringtable;
	struct nlist_64	*array;

	array = (void *)ptr + symoff;
	stringtable = (void *) ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

int	nm_64(void *ptr, uint64_t filesize)
{
	uint32_t										ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command *symtab;
	size_t										i;

	if (filesize < sizeof(struct mach_header_64))
		return (EXIT_FAILURE);

	// Get the header that has all infos
	header = (struct mach_header_64 *)ptr;

	// Get the number of commands of the binary file
	ncmds = header->ncmds;

	// Get the start of the load commands
	// The load commands directly follow the mach_header
	lc = (struct load_command *) (ptr + sizeof(struct mach_header_64));

	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *) lc;

			print(symtab->nsyms, symtab->symoff, symtab->stroff, ptr);
			break ;
		}

		// Each command type has a structure specifically for it.
		// The cmdsize field is the size in bytes
 		// of the particular load command structure plus anything that follows it that
 		// is a part of the load command
		lc = (struct load_command *) ((void *)lc + lc->cmdsize);

		// The cmdsize for 32-bit architectures
 		// MUST be a multiple of 4 bytes and for 64-bit architectures MUST be a multiple
 		// of 8 bytes (these are forever the maximum alignment of any load commands).

		i++;
	}

	return (1);
}
int	nm_32(void *ptr, uint64_t filesize)
{
	uint32_t										ncmds;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*symtab;
	uint32_t				filetype;
	uint32_t										i;

	if (filesize < sizeof(struct mach_header))
		return (mach_o_error(MACH_O_ERROR_INVALID_MACH_HEADER));

	// Get the header that has all infos
	header = (struct mach_header*)ptr;

	filetype = header->filetype;

	if (is_valid_filetype(filetype) == false)
		return (mach_o_error(MACH_O_ERROR_INVALID_FILETYPE));

	// Get the number of commands of the binary file
	ncmds = header->ncmds;

	// Check if the size of the file allow load commands to exists
	if (filesize < (sizeof(struct mach_header) + sizeof(struct load_command)))
		return (mach_o_error(MACH_O_ERROR_INVALID_MACH_HEADER));

	// Get the start of the load commands
	// The load commands directly follow the mach_header
	lc = (struct load_command *) (ptr + sizeof(struct mach_header));

	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *) lc;

			print(symtab->nsyms, symtab->symoff, symtab->stroff, ptr);
			break ;
		}

		// Each command type has a structure specifically for it.
		// The cmdsize field is the size in bytes
 		// of the particular load command structure plus anything that follows it that
 		// is a part of the load command
		lc = (struct load_command *) ((void *)lc + lc->cmdsize);

		// The cmdsize for 32-bit architectures
 		// MUST be a multiple of 4 bytes and for 64-bit architectures MUST be a multiple
 		// of 8 bytes (these are forever the maximum alignment of any load commands).

		i++;
	}

	return (1);
}

/*
** 1) Check magic number
*/

int	nm(void *ptr, uint64_t filesize)
{
	uint32_t	magic_number;

	// Get the magic number at the start of the file
	magic_number = *(uint32_t*)ptr;

	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		return (nm_64(ptr, filesize));

	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		return (nm_32(ptr, filesize));

	// When it is a fat arhc
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		return (nm_32(ptr, filesize));

	// When it is a fat arhc 64 bits
	if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
		return (nm_64(ptr, filesize));

	return (mach_o_error(MACH_O_ERROR_INVALID_MAGICK));
}

int	exec(char *filename)
{
	void		*ptr;
	uint64_t	filesize;

	// 1) Load the files
	if ((ptr = map_loading_file(filename, &filesize)) == NULL)
		return (EXIT_FAILURE);

	// The file is lesser than uint32_t, its an error
	// Because we need at least uint32_t to read a magick number
	if (filesize < sizeof(uint32_t))
		return (EXIT_FAILURE);

	// 2) Now we exec nm on the file
	if (!nm(ptr, filesize))
		return (EXIT_FAILURE);

	// 3) Then we free the memory asked to store the file content
	if (map_unloading_file(ptr, filesize) == -1)
		return (EXIT_FAILURE);

	return (EXIT_OK);
}

int	main(int ac, char **av)
{
	int				i;
	int				exit_value;
	t_options	options;

	exit_value = EXIT_SUCCESS;
	i = 1;

	if (read_options_arguments(ac, av, &options) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// Read every arg
	while (i < ac)
	{
		if (exec(av[i]) == EXIT_FAILURE)
			exit_value = EXIT_FAILURE;
		i++;
	}

	// END THE PROGRAM
	return (exit_value);
}
