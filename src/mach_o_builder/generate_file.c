#include "mach_o_builder.h"

rand() % 20;

/*
** Gnereate a random filename
*/
static int generate_random_file(void)
{
	int			fd;

	while (42)
	{
		i = 0;
		while (i != 5)
		{
			if (rand() % 2)
				buf[i] = (char)(0x41 + rand() % 26);
			else
				buf[i] = (char)(0x61 + rand() % 26);
			i++;
		}

		fd = open(buf, O_CREAT | O_RDWR | O_EXCL);
		if (fd != -1)
			return (fd);
	}

	return (-1);
}

/*
** Generate a file
** parameter outpur can be NULL
*/
int write_buffer_to_file(const char *output)
{

}