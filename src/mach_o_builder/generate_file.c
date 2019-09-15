#include "mach_o_builder.h"

#define RANDOM_FILE_SIZE 5

/*
** Gnereate a random filename
*/

static int generate_random_file(void)
{
	int			fd;
	int			x;
	int			i;
	char		buf[RANDOM_FILE_SIZE + 18];

	x = 0;
	while (x < 20)
	{
		i = 0;
		while (i != RANDOM_FILE_SIZE)
		{
			if (rand() % 2)
				buf[i] = (char)(0x41 + rand() % 26);
			else
				buf[i] = (char)(0x61 + rand() % 26);
			i++;
		}

		memcpy(buf + i, ".mach-o-builder.o\0", 18);

		fd = open(buf, O_CREAT | O_RDWR | O_EXCL);

		if (fd != -1)
			return (-1);
	}

	return (-1);
}

/*
** Generate a file
** parameter outpur can be NULL
*/
int write_buffer_to_file(const char *output, const char *buffer, size_t size)
{
	int	fd;
	
	if (NULL == output)
		fd = generate_random_file();
	else
		fd = open(output, O_CREAT | O_RDWR | O_EXCL);

	return write(fd, buffer, size);
}
