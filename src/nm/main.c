#include "nm.h"

/*
 *	nm
*/

void print(int nsyms, int symoff, int stroff, char *ptr)
{
	int							i;
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

int	nm_64(void *ptr)
{
	int										ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command *symtab;
	int										i;
	struct symtab_command * sym;

	/*
	** A variable length string in a load command is represented by an lc_str
	** 	union.  union lc_str {
	**        uint32_t        offset;
	** 	#ifndef __LP64__
	** 	       char            *ptr;
	** 	#endif
	** };
	*/
	union lc_str					str;


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
			sym = (struct symtab_command *) lc;

			print(symtab->nsyms, symtab->symoff, symtab->stroff);
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

int	nm(void *ptr)
{
	int	magic_number;

	// Get the magic number at the start of the file
	magic_number = *(int *)ptr;

	if (magic_number == MH_MAGIC_64)
		return nm_64(ptr);

	return (1);
}

int	exec(int fd)
{
	void		*ptr;
	struct stat	buf;
	int		file_type;

	// 1) We read the file
	if (fstat(fd, &buf) < 0)
		return (0);

	// 2) Get the file type
	file_type = buf.st_mode & S_IFMT;

	// Check if the open file is a file
	// Not a directory or a link
	if (file_type != S_IFREG
	&& file_type != S_IFLNK)
	return (0);

	if ((ptr = mmap(0, buf.st_size,
		PROT_READ, PROT_WRITE,
		fd, 0)) == MAP_FAILED)
		return (0);

	// 3) Now we exec nm on the file
	if (!nm(ptr))
		return (0);

	// 4) Then we free the memory asked to store the file content
	if (munmap(ptr, buf.st_size) < 0)
		return (0);

	return (1);
}

int	main(int ac, char **av)
{
	int	i;
	int	fd;
	int	exit_value;
	t_options options;

	exit_value = EXIT_SUCCESS;
	i = 1;

	if (read_options_arguments(ac, av, &options) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	// Read every arg
	while (i < ac)
	{
		// Try to open the file passed as arg
		if ((fd = open(av[i], O_RDONLY)) == -1)
			exit_value = EXIT_FAILURE;
		else
		{
			// The file has been opened successfully
			// Then we process the file
			if (!exec(fd))
				exit_value = EXIT_FAILURE;
		}
		i++;
	}

	// END THE PROGRAM
	return (exit_value);
}
