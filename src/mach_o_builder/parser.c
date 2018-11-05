#include "mach_o_builder.h"

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

static const char *mach_header_keys_map_g[] = {
  "magic_number",
  "cputype",
  "cpusubtype",
  "filetype",
  "ncmds",
  "sizeofcmds",
  "flags",
  "reserved",
  NULL,
};

/*
** struct load_command {
**        uint32_t cmd;           // type of load command
**        uint32_t cmdsize;       // total size of command in bytes
** };
*/

static const char *load_command_g[] = {
  "cmd",
  "cmdsize",
  "section_architecture",
  NULL,
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

static const char *section_keys_map_g[] = {
  "section_type",
  "sectname[16]",
  "segname[16]",
  "addr",
  "size",
  "offset",
  "align",
  "reloff",
  "nreloc",
  "flags",
  "reserved1",
  "reserved2",
  NULL,
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

  const char **map[] = {
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
    while (map[i][j])
    {
      if (!ft_strcmp(map[i][j], str))
      {
        // If the state does not accept this key
        if ((int)i != state)
            ret = 0;
        else
          return (1);

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

/*
** The state variable tells where are in the parsing routine
** Are we waiting the header ?
** Are we waiting a load command ?
*/

int build_mach_o_from_conf(t_mach_o_builder *builder, const char *path)
{
	int		fd;
	char	*line;
  char  **property;
  int    state;
  int    ret;

	fd = load_file_descriptor(path);

  (void)builder;

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

    clear_array(property);
    free(line);
	}

	return (0);
}
