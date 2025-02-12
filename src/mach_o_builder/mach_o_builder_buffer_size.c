#include "mach_o_builder.h"

static const int BITS_64 = 2;

/*
** =====> SEGMENT SIZE
*/

static size_t get_segment_command_list_size(t_mach_o_builder *builder) {
  size_t                ret;
  t_list                *x;
  t_mach_o_segment      *segment;

  (void)segment;

  ret = 0;
  x = builder->segment_list;
  while (x) {
    ret += sizeof(t_mach_o_segment);

    // @TODO need to handle segment
    // segment = (struct symtab_command*)x->content;
    // ret += segment->section.section.size;

    x = x->next;
  }

  debug("Finsished zith get_segment_command_list_size\n");

  return (ret);
}

/*
** =====> SECTION SIZE
*/

static size_t get_section_command_list_size(t_mach_o_builder *builder) {
  size_t  ret;
  t_list                *x;
  t_mach_o_section *section;

  (void)section;
  ret = 0;
  x = builder->section_list;
  while (x) {
    ret += sizeof(t_mach_o_section);

    // @TODO need to handle section
    // section = (struct symtab_command*)x->content;
    // ret += section->section.section.size;

    x = x->next;
  }

  debug("Finsished zith get_section_command_list_size\n");

  return (ret);
}

/*
** =====> SYMTAB SIZE
*/

static size_t get_symtab_command_list_size(t_mach_o_builder *builder) {
  size_t  ret;
  t_list                *x;
  struct symtab_command *symtab;

  ret = 0;
  x = builder->symtab_list;
  while (x) {
    // @TODO need to handle symtab
    ret += sizeof(struct symtab_command);

    symtab = (struct symtab_command*)x->content;

    ret += symtab->strsize;

    x = x->next;
  }

  debug("Finsished zith get_symtab_command_list_size\n");

  return (ret);
}

/*
** =====> SYMBOL SIZE
*/

static size_t get_symbol_command_list_size(t_mach_o_builder *builder) {
  size_t  ret;
  t_list                *x;
  struct nlist_64       *symbol;

  ret = 0;
  x = builder->symbol_list;
  while (x) {
    // @TODO need to handle symbol
    ret += sizeof(struct nlist_64);

    symbol = (struct nlist_64*)x->content;

    x = x->next;
  }

  debug("Finsished zith get_symbol_command_list_size\n");

  return (ret);
}

static size_t get_string_table_size(t_mach_o_builder *builder) {
  size_t ret;

  ret = 0;

  if (NULL != builder->string_table)
    ret = ft_strlen(builder->string_table);

  debug("Finsished zith get_string_table_size\n");

  return (ret);
}

static size_t get_load_command_list_size(t_mach_o_builder *builder) {
  return get_segment_command_list_size(builder)
        + get_section_command_list_size(builder)
        + get_symtab_command_list_size(builder)
        + get_symbol_command_list_size(builder)
        + get_string_table_size(builder);
}

/*
** Read the builder, and provide a buff size
** take into account the arhcitecture provided of the header and each command
*/

size_t get_buffer_size_from_builder(t_mach_o_builder *builder){
  size_t  ret;

  // Set the header size
  ret = sizeof(struct mach_header);
  if (builder->header_architecture == BITS_64) {
    ret = sizeof(struct mach_header_64);
  }

  // Set the size of each load command
  ret += get_load_command_list_size(builder);

  debug("ret : %ld\n", ret);

  return (ret);
}
