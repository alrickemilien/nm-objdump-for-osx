#include "mach_o_builder.h"

/*
** This static variable is mandatory
** it is filed during the parsing
** Each sub map are filled zith pointeur on variables on this stati variable
* At the end, the builder passed as parameter will be strictly memcopy from this static
*/

static t_mach_o_builder builder;

/*
** Handled and allowed types for the parsed variables
*/

enum {
  STRING_TYPE = 0UL,
  UINT32_TYPE,
  UINT64_TYPE,
};

enum {
  GLOBAL_CONFIGURATION_STATE = 0UL,
  HEADER_STATE,
  FAT_HEADER_STATE,
  LOAD_COMMAND_STATE,
  SECTION_COMMAND_STATE,
  FAT_ARCH_STATE,
  SEGMENT_COMMAND_STATE,
  SYMTAB_COMMAND_STATE,
  DATA_STATE,
};

  // Must be in the same order as the enum right before
  static const char *state_keys_g[] = {
    "[GLOBAL_CONFIGURATION]",
    "[HEADER]",
    "[FAT_HEADER]",
    "[LOAD_COMMAND]",
    "[SECTION_COMMAND]",
    "[FAT_ARCH]",
    "[SEGMENT_COMMAND]",
    "[SYMTAB_COMMAND]",
    "[DATA_SECTION]",
    NULL,
  };

  struct mapping {
    // Key in the configuration file
    char   *key;

    // Pointeur zhere ze zill store the value
    void   *value;

    // Type of the value (char*, uint32_t, uint64_t)
    uint32_t type;
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
    { "magic_number", &builder.header.header.magic, UINT32_TYPE },
    { "cputype", &builder.header.header.cputype, UINT32_TYPE },
    { "cpusubtype", &builder.header.header.cpusubtype, UINT32_TYPE },
    { "filetype", &builder.header.header.filetype, UINT32_TYPE },
    { "ncmds", &builder.header.header.ncmds, UINT32_TYPE },
    { "sizeofcmds", &builder.header.header.sizeofcmds, UINT32_TYPE },
    { "flags", &builder.header.header_64.flags, UINT32_TYPE },
    { "reserved", &builder.header.header_64.reserved, UINT32_TYPE },
    { NULL, NULL, 0 },
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
    { "cputype", &builder.fat_arch.fat_arch.cputype, UINT32_TYPE },
    { "cpusubtype", &builder.fat_arch.fat_arch.cpusubtype, UINT32_TYPE },
    { "offset", &builder.fat_arch.fat_arch.offset, UINT64_TYPE },
    { "size", &builder.fat_arch.fat_arch.size, UINT32_TYPE },
    { "align", &builder.fat_arch.fat_arch.align, UINT32_TYPE },
    { "reserved", &builder.fat_arch.fat_arch_64.reserved, UINT32_TYPE },
    { NULL, NULL, 0 },
  };

  /*
  ** struct fat_header {
  **        uint32_t        magic;          // FAT_MAGIC or FAT_MAGIC_64
  **        uint32_t        nfat_arch;      // number of structs that follow
  ** };
  */

  static const struct mapping mach_fat_header_keys_map_g[] = {
    { "magic", &builder.fat_header.magic, UINT32_TYPE },
    { "nfat_arch", &builder.fat_header.nfat_arch, UINT32_TYPE },
    { NULL, NULL, 0 },
  };

  /*
  ** struct load_command {
  **        uint32_t cmd;           // type of load command
  **        uint32_t cmdsize;       // total size of command in bytes
  ** };
  */

  static const struct mapping load_command_g[] = {
    { "cmd", &builder.load_command.lc.cmd, UINT32_TYPE },
    { "cmdsize", &builder.load_command.lc.cmdsize, UINT32_TYPE },
    { "section_architecture", &builder.load_command.section_architecture, UINT32_TYPE },
    { NULL, NULL, 0 },
  };

/*
** struct segment_command { //for 32-bit architectures
**         uint32_t        cmd;            // LC_SEGMENT
**         uint32_t        cmdsize;        // includes sizeof section structs
**         char            segname[16];    // segment name
**         uint32_t        vmaddr;         // memory address of this segment
**         uint32_t        vmsize;         // memory size of this segment
**         uint32_t        fileoff;        // file offset of this segment
**         uint32_t        filesize;       // amount to map from the file
**         vm_prot_t       maxprot;        // maximum VM protection
**         vm_prot_t       initprot;       // initial VM protection
**         uint32_t        nsects;         // number of sections in segment
**         uint32_t        flags;          // flags
** };
**
** struct segment_command_64 { // for 64-bit architectures
**         uint32_t        cmd;            // LC_SEGMENT_64
**         uint32_t        cmdsize;        // includes sizeof section_64 structs
**         char            segname[16];    // segment name
**         uint64_t        vmaddr;         // memory address of this segment
**         uint64_t        vmsize;         // memory size of this segment
**         uint64_t        fileoff;        // file offset of this segment
**         uint64_t        filesize;       // amount to map from the file
**         vm_prot_t       maxprot;        // maximum VM protection
**         vm_prot_t       initprot;       // initial VM protection
**         uint32_t        nsects;         // number of sections in segment
**         uint32_t        flags;          // flags
** };
*/
static const struct mapping mach_segment_command_keys_map_g[] = {
  { "cmd", &builder.segment.segment_64.cmd, UINT32_TYPE },
  { "cmdsize", &builder.segment.segment_64.cmdsize, UINT32_TYPE },
  { "segname", &builder.segment.segment_64.segname, UINT32_TYPE },
  { "vmaddr", &builder.segment.segment_64.vmaddr, UINT64_TYPE },
  { "vmsize", &builder.segment.segment_64.vmsize, UINT64_TYPE },
  { "fileoff", &builder.segment.segment_64.fileoff, UINT64_TYPE },
  { "filesize", &builder.segment.segment_64.filesize, UINT64_TYPE },
  { "maxprot", &builder.segment.segment_64.maxprot, UINT32_TYPE },
  { "initprot", &builder.segment.segment_64.initprot, UINT32_TYPE },
  { "nsects", &builder.segment.segment_64.nsects, UINT32_TYPE },
  { "flags", &builder.segment.segment_64.flags, UINT32_TYPE },
  { NULL, NULL, 0 },
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
    {"sectname[16]", &builder.section.section.sectname, STRING_TYPE },
    {"segname[16]", &builder.section.section.segname, STRING_TYPE },
    {"addr", &builder.section.section.addr, UINT64_TYPE },
    {"size", &builder.section.section.size, UINT64_TYPE },
    {"offset", &builder.section.section.offset, UINT32_TYPE },
    {"align", &builder.section.section.align, UINT32_TYPE },
    {"reloff", &builder.section.section.reloff, UINT32_TYPE },
    {"nreloc", &builder.section.section.nreloc, UINT32_TYPE },
    {"flags", &builder.section.section.flags, UINT32_TYPE },
    {"reserved1", &builder.section.section.reserved1, UINT32_TYPE },
    {"reserved2", &builder.section.section.reserved2, UINT32_TYPE },
    {"reserved3", &builder.section.section_64.reserved2, UINT32_TYPE },
    { NULL, NULL, 0 },
  };

  /*
  ** struct symtab_command {
  **         uint32_t        cmd;            // LC_SYMTAB
  **         uint32_t        cmdsize;        // sizeof(struct symtab_command)
  **         uint32_t        symoff;         // symbol table offset
  **         uint32_t        nsyms;          // number of symbol table entries
  **         uint32_t        stroff;         // string table offset
  **         uint32_t        strsize;        // string table size in bytes
  ** };
  */

  static const struct mapping symtab_keys_map_g[] = {
    {"cmd", &builder.symtab.cmd, UINT32_TYPE },
    {"cmdsize", &builder.symtab.cmdsize, UINT32_TYPE },
    {"symoff", &builder.symtab.symoff, UINT32_TYPE },
    {"nsyms", &builder.symtab.nsyms, UINT32_TYPE },
    {"stroff", &builder.symtab.stroff, UINT32_TYPE },
    {"strsize", &builder.symtab.strsize, UINT32_TYPE },
    { NULL, NULL, 0 },
  };

  static const struct mapping global_configuration_keys_map_g[] = {
    { NULL, NULL, 0 },
  };

  /*
  ** The following array map must respect in order the enum
  ** by their index / position inthe map
  **  GLOBAL_CONFIGURATION_STATE = 0UL,
  **  HEADER_STATE,
  **  FAT_HEADER_STATE,
  **  LOAD_COMMAND_STATE,
  **  SECTION_COMMAND_STATE,
  **  FAT_ARCH_STATE,
  **  SYMTAB_COMMAND_STATE,
  **  SEGMENT_COMMAND_STATE,
  */

  static const struct mapping *map[] = {
    global_configuration_keys_map_g,
    mach_header_keys_map_g,
    mach_fat_header_keys_map_g,
    load_command_g,
    section_keys_map_g,
    mach_fat_arch_keys_map_g,
    mach_segment_command_keys_map_g,
    symtab_keys_map_g,
    NULL,
  };

/*
** Find key among global static array of the file
** return false when not found
** Return -1 when key is not recognized
** Return 0 when key is not allowed during this state
** Return 1 when ok
*/

static int find_valid_key(const char *str, int state)
{
  size_t j;
  int   ret;

  ret = -1;

  j = 0;
  while (map[state][j].key)
  {
    if (!ft_strcmp(map[state][j].key, str))
    {
      return (j);
    }

    j++;
  }

  return (ret);
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
  uint64_t value;

  // Handle each type of data
  if (map[state][index].type == STRING_TYPE) {
    // @TODO need to copy jusauau next \n or \0
    memcpy(map[state][index].value, value_str, 1);

  } else if (map[state][index].type == UINT32_TYPE) {
    value = atoi_base(value_str, 16);
    *(uint32_t*)map[state][index].value = (uint32_t)value;

  } else if (map[state][index].type == UINT64_TYPE) {
    value = atoi_base(value_str, 16);
    *(uint64_t*)map[state][index].value = (uint64_t)value;
  }
}

/*
** Append data to the corresponding list in t_mach_o_builder structure
** A SYMTAB will go to symtab list
** A SEGMENT will go to segment list
** ...
*/

static void append_data_to_corresponding_state_list(int state)
{
  size_t i;

  struct map_list_state {
    int state;
    void *list;
    void *value_in_builder;
    size_t size_value_in_builder;
  };

  const struct map_list_state list_map[] = {
    { LOAD_COMMAND_STATE, &builder.load_command_list, &builder.load_command, sizeof(struct load_command) },
    { SEGMENT_COMMAND_STATE, &builder.segment_list, &builder.segment, sizeof(t_mach_o_segment) },
    { SECTION_COMMAND_STATE, &builder.section_list, &builder.section, sizeof(t_mach_o_section) },
    { FAT_ARCH_STATE, &builder.fat_arch_list, &builder.fat_arch, sizeof(t_mach_o_fat_arch) },
    { SYMTAB_COMMAND_STATE, &builder.symtab_list, &builder.symtab, sizeof(struct symtab_command) },

    // End of the map
    { -1, NULL, NULL, 0 },
  };

  i = 0;
  while (list_map[i].state != -1)
  {
    if (list_map[i].state == state) {
      // Add the strcture to the list
      ft_lstadd(list_map[i].list,
        ft_lstnew(list_map[i].value_in_builder, list_map[i].size_value_in_builder));

      return ;
    }

    i++;
  }
}

/*
** Parse a single line of the file config
*/

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

  // It means that the last command is toappend to a list
  if (current_state != *state)
    append_data_to_corresponding_state_list(*state);

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

  memset(&builder, 0, sizeof(t_mach_o_builder));

  state = GLOBAL_CONFIGURATION_STATE;
	while(get_next_line(fd, &line) > 0) {
    debug("%s\n", line);
    parse_line(line, &state);
    debug_s("ok\n");
    free(line);
  }

  // When only one load_command has been given
  if (NULL == builder.load_command_list && state != HEADER_STATE && state != FAT_HEADER_STATE) {
    ft_lstadd(&builder.load_command_list,
      ft_lstnew(&builder.load_command, sizeof(t_mach_o_load_command)));
  }

  memcpy(b, &builder, sizeof(t_mach_o_builder));

	return (0);
}
