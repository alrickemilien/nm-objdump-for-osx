#include "mach_o_builder.h"

static const int BITS_64 = 2;

/*
** Read the builder, and provide a buff size
** take into account the arhcitecture provided of the header and each command
*/

static size_t get_buffer_size_from_builder(t_mach_o_builder *builder){
  size_t  ret;
  t_list  *x;
  t_mach_o_command *cmd;

  // Set the header size
  ret = sizeof(struct mach_header);
  if (builder->header_architecture == BITS_64)
    ret = sizeof(struct mach_header_64);

  x = builder->cmd_list;
  while (x) {
    ret += sizeof(struct load_command);

    cmd = (t_mach_o_command*)x->content;

    if (cmd->section_architecture == BITS_64)
      ret += sizeof(struct section_64);
    else
      ret += sizeof(struct section);

    debug_s("lqlqlqlq\n");

    x = x->next;
  }

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

/*
** Copy each commands from the list
** into the buffer
*/

static void copy_commands(t_mach_o_builder *builder, void *buffer, size_t *cursor) {
  t_list            *x;
  t_mach_o_command  *cmd;

  x = builder->cmd_list;
  while (x) {
    cmd = (t_mach_o_command*)x->content;

    // Copy load command datas
    memcpy(buffer + *cursor, &cmd->lc, sizeof(struct load_command));
    *cursor += sizeof(struct load_command);

    // Copy section datas
    if (cmd->section_architecture == BITS_64) {
      memcpy(buffer + *cursor, &cmd->section.section_64, sizeof(struct section_64));
      *cursor += sizeof(struct section_64);
    } else {
      memcpy(buffer + *cursor, &cmd->section.section, sizeof(struct section));
      *cursor += sizeof(struct section);
    }

    x = x->next;
  }
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

  copy_commands(builder, *buffer, &cursor);

  return (0);
}
