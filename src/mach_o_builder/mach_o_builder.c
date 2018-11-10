#include "mach_o_builder.h"

static const int BITS_64 = 2;

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
  size_t            i;

  i = 0;
  x = builder->segment_list;
  while (x) {
    segment = (t_mach_o_segment*)x->content;

    // Copy load command datas
    // @TODO need to handle 64bits structure
    memcpy(buffer + *cursor, segment, sizeof(struct segment_command));
    *cursor += sizeof(struct segment_command);

    i++;
    x = x->next;
  }
  debug("Number of segment : %ld\n", i);
}

static void copy_section_command_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list            *x;
  t_mach_o_section  *section;
  size_t            i;

  i = 0;
  x = builder->section_list;
  while (x) {
    section = (t_mach_o_section*)x->content;

    // Copy load command datas
    // @TODO need to handle 64bits structure
    memcpy(buffer + *cursor, section, sizeof(struct segment_command));
    *cursor += sizeof(struct section);

    x = x->next;
    i++;
  }
  debug("Number of section : %ld\n", i);
}

static void copy_symtab_command_data(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list                 *x;
  struct symtab_command  *symtab;
  size_t            i;

  i = 0;
  x = builder->symtab_list;
  while (x) {
    symtab = (struct symtab_command*)x->content;

    // Copy load command datas
    memcpy(buffer + *cursor, symtab, sizeof(struct symtab_command));
    *cursor += sizeof(struct symtab_command);

    x = x->next;
    i++;
  }
  debug("Number of symtab : %ld\n", i);
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
