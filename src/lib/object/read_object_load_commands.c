#include "mach_o.h"

struct load_command	*read_object_load_commands(t_mach_o *file)
{
	if (file->mh)
		file->load_commands = (struct load_command*)(file->mh + 1);
	else if (file->mh_64)
		file->load_commands = (struct load_command*)(file->mh_64 + 1);
	else
		return (NULL);
	if (check_file_addr_size(file,
		    				file->load_commands,
							sizeof(struct load_command)) == -1)
	{
		printf("WTF\n");
		file->load_commands = NULL;
		return (NULL);
	}
	return (file->load_commands);
}