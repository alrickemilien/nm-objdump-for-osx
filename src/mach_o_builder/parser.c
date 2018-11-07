#include "mach_o_builder.h"


struct mapping {
  char *key;
  void *value;
};

static t_mach_o_builder builder;

  static const char *state_keys_g[] = {
    "[HEADER]",
    "[LOAD_COMMAND]",
    "[SECTION_COMMAND]",
    NULL,
  };

  /*
  ** struct mach_header {
  **         uint32_t        magic;          // mach magic number identifier
  **         cpu_type_t      cputype;        // cpu specifier
  **         cpu_subtype_t   cpusubtype;     // machine specifier
  **         uint32_t        filetype;       // type of file
  **         uint32_t        ncmds;          // number of load commands
  **         uint32_t        sizeofcmds;     // the size of all the load commands
  **         uint32_t        flags;          // flags
  ** };
  **
  ** struct mach_header_64 {
  **         uint32_t        magic;          // mach magic number identifier
  **         cpu_type_t      cputype;        // cpu specifier
  **         cpu_subtype_t   cpusubtype;     // machine specifier
  **         uint32_t        filetype;       // type of file
  **         uint32_t        ncmds;          // number of load commands
  **         uint32_t        sizeofcmds;     // the size of all the load commands
  **         uint32_t        flags;          // flags
  **         uint32_t        reserved;       // reserved
  ** };
  */

  static const struct mapping mach_header_keys_map_g[] = {
    { "magic_number", &builder.header.header.magic },
    { "cputype", &builder.header.header.cputype },
    { "cpusubtype", &builder.header.header.cpusubtype },
    { "filetype", &builder.header.header.filetype },
    { "ncmds", &builder.header.header.ncmds },
    { "sizeofcmds", &builder.header.header.sizeofcmds },
    { "flags", &builder.header.header_64.flags },
    { "reserved", &builder.header.header_64.reserved },
    { NULL, NULL},
  };

  /*
  ** struct load_command {
  **        uint32_t cmd;           // type of load command
  **        uint32_t cmdsize;       // total size of command in bytes
  ** };
  */

  static const struct mapping load_command_g[] = {
    { "cmd", &builder.cmd->lc.cmd },
    { "cmdsize", &builder.cmd->lc.cmdsize },
    { "section_architecture", &builder.cmd->lc.section_architecture },
    { NULL, NULL},
  };

  /*
  ** struct section { // for 32-bit architectures
  **         char            sectname[16];   // name of this section
  **         char            segname[16];    // segment this section goes in
  **         uint32_t        addr;           // memory address of this section
  **         uint32_t        size;           // size in bytes of this section
  **         uint32_t        offset;         // file offset of this section
  **         uint32_t        align;          // section alignment (power of 2)
  **         uint32_t        reloff;         // file offset of relocation entries
  **         uint32_t        nreloc;         // number of relocation entries
  **         uint32_t        flags;          // flags (section type and attributes
  **         uint32_t        reserved1;      // reserved (for offset or index)
  **         uint32_t        reserved2;      // reserved (for count or sizeof)
  ** };
  **
  ** struct section_64 { // for 64-bit architectures
  **         char            sectname[16];   // name of this section
  **         char            segname[16];    // segment this section goes in
  **         uint64_t        addr;           // memory address of this section
  **         uint64_t        size;           // size in bytes of this section
  **         uint32_t        offset;         // file offset of this section
  **         uint32_t        align;          // section alignment (power of 2)
  **         uint32_t        reloff;         // file offset of relocation entries
  **         uint32_t        nreloc;         // number of relocation entries
  **         uint32_t        flags;          // flags (section type and attributes
  **         uint32_t        reserved1;      // reserved (for offset or index)
  **         uint32_t        reserved2;      // reserved (for count or sizeof)
  **         uint32_t        reserved3;      // reserved
  ** };
  */

  static const struct mapping section_keys_map_g[] = {
    {"section_type", &builder.cmd->section.section_type },
    {"sectname[16]", &builder.cmd->section.sectname },
    {"segname[16]", &builder.cmd->section.segname },
    {"addr", &builder.cmd->section.addr },
    {"size", &builder.cmd->section.size },
    {"offset", &builder.cmd->section.offset },
    {"align", &builder.cmd->section.align },
    {"reloff", &builder.cmd->section.reloff },
    {"nreloc", &builder.cmd->section.nreloc },
    {"flags", &builder.cmd->section.flags },
    {"reserved1", &builder.cmd->section.reserved1 },
    {"reserved2", &builder.cmd->section.reserved2 },
    {"reserved3", &builder.cmd->section_64.reserved2 },
    { NULL, NULL},
  };

static const int HEADER_STATE = 0;
//static const int LOAD_COMMAND_STATE = 1;

/*
** Find key among global static array of the file
** return false when not found
** Return -1 when key is not recognized
** Return 0 when key is not allowed during this state
** Return 1 when ok
*/

static int find_valid_key(const char *str, int state)
{
  size_t i;
  size_t j;
  int   ret;

  (void)state;

  const struct mapping *map[] = {
    mach_header_keys_map_g,
    load_command_g,
    section_keys_map_g,
    NULL,
  };

  i = 0;
  ret = -1;
  while(map[i])
  {
    j = 0;
    while (map[i][j].key)
    {
      if (!ft_strcmp(map[i][j].key, str))
      {
        // If the state does not accept this key
        if ((int)i != state)
            ret = 0;
        else
          return (j);

      }

      j++;
    }

    i++;
  }

  return (ret);
}

/*
** Remove blank chars arround each word of the given array of word
*/

static void trim_each_string_of_array(char **arr)
{
  size_t   i;
  char  *tmp;

  i = 0;
  while (arr[i])
  {
    tmp = ft_strtrim(arr[i]);

    free(arr[i]);

    arr[i] = tmp;

    i++;
  }
}

/*
** Realease the memory of an array of char*
*/

static void clear_array(char **arr)
{
  size_t   i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);

    i++;
  }

  free(arr);
}

/*
** Check if it is a state indication like [HEADER] or [LOAD_COMMAND]
** if it is, update the state passed as parameter
*/

static bool is_state_indication(const char *str, int *state)
{
  size_t i;

  i = 0;
  while (state_keys_g[i] != NULL)
  {
    if (!ft_strcmp(state_keys_g[i], str))
    {
      *state = (int)i;
      return (true);
    }
    i++;
  }

  return (false);
}

static void apply_property(int state, int key, const char *value_str)
{
  (void)state;
  (void)key;
  (void)value_str;
}


/*
** The state variable tells where are in the parsing routine
** Are we waiting the header ?
** Are we waiting a load command ?
*/

int build_mach_o_from_conf(t_mach_o_builder *b, const char *path)
{
	int		fd;
	char	*line;
  char  **property;
  int    state;
  int    ret;

	fd = load_file_descriptor(path);

	if (fd == -1)
		return (EXIT_FAILURE);

  state = HEADER_STATE;
	while(get_next_line(fd, &line) > 0)
	{
		property = ft_strsplit(line, '=');

    trim_each_string_of_array(property);

    if (NULL == *property)
      continue;

    // Check if it is a state indication
    if (is_state_indication(*(const char**)property, &state) == true)
      ;

    // Check the property
    else if ((ret = find_valid_key(property[0], state)) < 1) {
      if (*property[0] == '#')
        ;
      else if (ret == 0)
        printf("The property %s is not allowed "
              "for the state %s.\n", property[0], state_keys_g[state]);
      else if (ret == -1)
        printf("The property %s is not handled\n", property[0]);
    }

    if (ret > 0)
      apply_property(state, ret, property[3]);

    clear_array(property);
    free(line);
	}

  memcpy(b, &builder, sizeof(t_mach_o_builder));

	return (0);
}
