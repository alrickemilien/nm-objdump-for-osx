#include "mach_o_builder.h"

struct mapping {
  char *key;
  void *value;
};

static t_mach_o_builder builder;

  static const char *state_keys_g[] = {
    "[HEADER]",
    "[FAT_HEADER]",
    "[LOAD_COMMAND]",
    "[SECTION_COMMAND]",
    "[FAT_ARCH]",
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
  ** struct fat_arch {
  **        cpu_type_t      cputype;      // cpu specifier (int)
  **        cpu_subtype_t   cpusubtype;   // machine specifier (int)
  **        uint32_t        offset;       // file offset to this object file
  **        uint32_t        size;         // size of this object file
  **        uint32_t        align;        // alignment as a power of 2
  ** };
  **
  ** struct fat_arch_64 {
  **        cpu_type_t      cputype;    // cpu specifier (int)
  **        cpu_subtype_t   cpusubtype; // machine specifier (int)
  **        uint64_t        offset;     // file offset to this object file
  **        uint64_t        size;       // size of this object file
  **        uint32_t        align;      // alignment as a power of 2
  **        uint32_t        reserved;   // reserved
  ** };
  */

  static const struct mapping mach_fat_arch_keys_map_g[] = {
    { "cputype", &builder.fat_arch.fat_arch.cputype },
    { "cpusubtype", &builder.fat_arch.fat_arch.cpusubtype },
    { "offset", &builder.fat_arch.fat_arch.offset },
    { "size", &builder.fat_arch.fat_arch.size },
    { "align", &builder.fat_arch.fat_arch.align },
    { "reserved", &builder.fat_arch.fat_arch_64.reserved },
    { NULL, NULL},
  };

  /*
** struct fat_header {
**        uint32_t        magic;          // FAT_MAGIC or FAT_MAGIC_64 
**        uint32_t        nfat_arch;      // number of structs that follow 
** };
  */
  static const struct mapping mach_fat_header_keys_map_g[] = {
    { "magic", &builder.fat_header.magic },
    { "nfat_arch", &builder.fat_header.nfat_arch },
    { NULL, NULL},
  };

  /*
  ** struct load_command {
  **        uint32_t cmd;           // type of load command
  **        uint32_t cmdsize;       // total size of command in bytes
  ** };
  */

  static const struct mapping load_command_g[] = {
    { "cmd", &builder.cmd.lc.cmd },
    { "cmdsize", &builder.cmd.lc.cmdsize },
    { "section_architecture", &builder.cmd.section_architecture },
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
    {"sectname[16]", &builder.cmd.section.section.sectname },
    {"segname[16]", &builder.cmd.section.section.segname },
    {"addr", &builder.cmd.section.section.addr },
    {"size", &builder.cmd.section.section.size },
    {"offset", &builder.cmd.section.section.offset },
    {"align", &builder.cmd.section.section.align },
    {"reloff", &builder.cmd.section.section.reloff },
    {"nreloc", &builder.cmd.section.section.nreloc },
    {"flags", &builder.cmd.section.section.flags },
    {"reserved1", &builder.cmd.section.section.reserved1 },
    {"reserved2", &builder.cmd.section.section.reserved2 },
    {"reserved3", &builder.cmd.section.section_64.reserved2 },
    { NULL, NULL},
  };

static const int HEADER_STATE = 0;
static const int FAT_HEADER_STATE = 1;
static const int LOAD_COMMAND_STATE = 2;
static const int SECTION_COMMAND_STATE = 3;
//static const int FAT_ARCH_STATE = 4;

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
    mach_fat_header_keys_map_g,
    load_command_g,
    section_keys_map_g,
    mach_fat_arch_keys_map_g,
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

static void apply_property(int state, int index, const char *value_str)
{
  int value;

  const struct mapping *map[] = {
    mach_header_keys_map_g,
    mach_fat_header_keys_map_g,
    load_command_g,
    section_keys_map_g,
    mach_fat_arch_keys_map_g,
    NULL,
  };

  value = atoi_base(value_str, 16);

  *(uint32_t*)map[state][index].value = (uint32_t)value;
}

static void parse_line(const char *line, int *state)
{
  char  **property;
  int   ret;
  int   current_state;

  current_state = *state;

  property = ft_strsplit(line, '=');

  trim_each_string_of_array(property);

  if (NULL == *property)
    return ;

  ret = 0;

  // Check if it is a current_state indication
  if (is_state_indication(*(const char**)property, &current_state) == true)
    ;

  // Check the property
  else if ((ret = find_valid_key(property[0], current_state)) < 1) {
    if (*property[0] == '#')
      ;
    else if (ret == 0)
      debug("The property %s is not allowed "
            "for the current_state %s.\n", property[0], state_keys_g[current_state]);
    else if (ret == -1)
      debug("The property %s is not handled\n", property[0]);
  }

  // It means that the last command was a section and we are reading a new one
  // we need to push it to the cmd list
  if (current_state == LOAD_COMMAND_STATE && *state == SECTION_COMMAND_STATE)
    ft_lstadd(&builder.cmd_list, ft_lstnew(&builder.cmd, sizeof(t_mach_o_command)));

  // Update the state
  *state = current_state;

  if (ret > 0)
    apply_property(current_state, ret, property[1]);

  clear_array(property);
}

/*
** The state variable tells where are in the parsing routine
** Are we waiting the header ?
** Are we waiting a load command ?
*/

int build_mach_o_from_conf(t_mach_o_builder *b, const char *path)
{
	int   fd;
	char  *line;
  int   state;

	fd = load_file_descriptor(path);

	if (fd == -1)
		return (EXIT_FAILURE);

  state = HEADER_STATE;
  builder.cmd_list= NULL;
	while(get_next_line(fd, &line) > 0) {
    debug("%s\n", line);
    parse_line(line, &state);
    debug_s("ok\n");
    free(line);
  }

  // When only one load_command has been given
  if (NULL == builder.cmd_list && state != HEADER_STATE && state != FAT_HEADER_STATE)
    ft_lstadd(&builder.cmd_list, ft_lstnew(&builder.cmd, sizeof(t_mach_o_command)));

  memcpy(b, &builder, sizeof(t_mach_o_builder));

	return (0);
}
