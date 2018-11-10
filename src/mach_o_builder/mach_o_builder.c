#include "mach_o_builder.h"

static const int BITS_64 = 2;

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

  return (ret);
}

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

  return (ret);
}

static size_t get_symtab_command_list_size(t_mach_o_builder *builder) {
  size_t  ret;
  t_list                *x;
  struct symtab_command *symtab;

  (void)symtab;
  ret = 0;
  x = builder->symtab_list;
  while (x) {
    ret += sizeof(struct symtab_command);

    // @TODO need to handle symtab
    // symtab = (struct symtab_command*)x->content;
    // ret += symtab->section.section.size;

    x = x->next;
  }

  return (ret);
}

static size_t get_load_command_list_size(t_mach_o_builder *builder) {
  return get_segment_command_list_size(builder)
        + get_section_command_list_size(builder)
        + get_symtab_command_list_size(builder);
}

/*
** Read the builder, and provide a buff size
** take into account the arhcitecture provided of the header and each command
*/

static size_t get_buffer_size_from_builder(t_mach_o_builder *builder){
  size_t  ret;

  // Set the header size
  ret = sizeof(struct mach_header);
  if (builder->header_architecture == BITS_64)
    ret = sizeof(struct mach_header_64);

  ret += get_load_command_list_size(builder);

  return (ret);
}

/*
** Copy the mach o header datas
*/

static void copy_header_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  // 64 bits
  if (builder->header_architecture == BITS_64){
    memcpy(buffer + *cursor, &builder->header.header_64, sizeof(struct mach_header_64));
    *cursor += sizeof(struct mach_header_64);
  }

  // 32 bits
  else {
    memcpy(buffer + *cursor, &builder->header.header, sizeof(struct mach_header));
    *cursor += sizeof(struct mach_header);
  }
}

static void copy_segment_command_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list            *x;
  t_mach_o_segment  *segment;

  x = builder->segment_list;
  while (x) {
    segment = (t_mach_o_segment*)x->content;

    // Copy load command datas
    // @TODO need to handle 64bits structure
    memcpy(buffer + *cursor, segment, sizeof(struct segment_command));
    *cursor += sizeof(struct segment_command);

    x = x->next;
  }
}

static void copy_section_command_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list            *x;
  t_mach_o_section  *section;

  x = builder->section_list;
  while (x) {
    section = (t_mach_o_section*)x->content;

    // Copy load command datas
    // @TODO need to handle 64bits structure
    memcpy(buffer + *cursor, section, sizeof(struct segment_command));
    *cursor += sizeof(struct section);

    x = x->next;
  }
}

static void copy_symtab_command_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list                 *x;
  struct symtab_command  *symtab;

  x = builder->symtab_list;
  while (x) {
    symtab = (struct symtab_command*)x->content;

    // Copy load command datas
    memcpy(buffer + *cursor, symtab, sizeof(struct symtab_command));
    *cursor += sizeof(struct symtab_command);

    x = x->next;
  }
}

/*
** Copy each commands from the list
** into the buffer
*/

static void copy_load_commands_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  copy_segment_command_data(builder, buffer, cursor);
  copy_symtab_command_data(builder, buffer, cursor);
  copy_section_command_data(builder, buffer, cursor);
}

static void copy_data_section_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  (void)builder;
  (void)buffer;
  (void)cursor;

  return;
}

/*
** Set the buffer of bytes into buffer provided as argument
** When an error occurs return -1
** else, when NO error occurs return 0
*/

int mach_o_builder(t_mach_o_builder *builder, void **buffer, size_t *size)
{
  size_t cursor;

  *size = get_buffer_size_from_builder(builder);

  *buffer = (void*)malloc(*size);

  if (NULL == *buffer)
    return (-1);

  cursor = 0;

  copy_header_data(builder, *buffer, &cursor);

  copy_load_commands_data(builder, *buffer, &cursor);

  copy_data_section_data(builder, *buffer, &cursor);

  debug("%ld bytes will be written to stdout\n", *size);

  return (0);
}
