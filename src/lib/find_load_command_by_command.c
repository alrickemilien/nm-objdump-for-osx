#include "mach_o.h"

/*
** This function returns the index of a specific load_command
** that corresponds to the uint32_t cmd given as parameter
*/

struct load_command	*find_load_command_by_command(
	t_mach_o *mach_o,
	uint32_t cmd)
{
	size_t             i;
	size_t             ncmds;
	struct load_command  *cursor_load_command;

  	// When the load_command or the magick number has not been set, return NULL
	if (NULL == mach_o->load_commands
	   || (NULL == mach_o->mh && NULL == mach_o->mh_64))
		return (NULL);

  i = 0;

	// printf("AAAAAAAAA\n");

  // Read ncmds from 32 or 64 bits structure, according to mh
  ncmds = mach_o->mh ? mach_o->mh->ncmds : mach_o->mh_64->ncmds;

	cursor_load_command = mach_o->load_commands;
	while (i < ncmds)
	{
		if (check_file_addr_size(mach_o, cursor_load_command,
								sizeof(struct load_command) == -1)
			|| check_file_addr_size(mach_o, cursor_load_command,
								cursor_load_command->cmdsize) == -1)
			return (NULL);

  	if (cmd == cursor_load_command->cmd
			|| (LC_REQ_DYLD | cmd) == cursor_load_command->cmd)
			return (cursor_load_command);

  		cursor_load_command =
			(struct load_command *)(void *)((uint8_t*)cursor_load_command
			+ cursor_load_command->cmdsize);

  		i++;
	}

  return (NULL);
}
