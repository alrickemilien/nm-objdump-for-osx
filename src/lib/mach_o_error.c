#include "mach_o.h"
#include <stdarg.h>

// static const t_mach_o_error g_macho_error[] = {
//   {
//     MACH_O_ERROR_INVALID_MAGICK,
//     MACH_O_ERROR_INVALID_MAGICK_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_FILE_SIZE,
//     MACH_O_ERROR_INVALID_FILE_SIZE_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_FILE,
//     MACH_O_ERROR_INVALID_FILE_STR,
//   },
//   {
//     MACH_O_ERROR_MAP_LOADING,
//     MACH_O_ERROR_MAP_LOADING_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_MACH_HEADER,
//     MACH_O_ERROR_INVALID_MACH_HEADER_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_FILETYPE,
//     MACH_O_ERROR_INVALID_FILETYPE_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_SYMBOL_TYPE,
//     MACH_O_ERROR_INVALID_SYMBOL_TYPE_STR,
//   },
//   {
//     MACH_O_ERROR_INVALID_FILE_TYPE,
//     MACH_O_ERROR_INVALID_FILE_TYPE_STR,
//   },
//   {
//     0,
//     NULL,
//   },
// };


static void out_buffer(const char *buffer, size_t *cursor, bool force)
{
  if (!force && (*cursor == 0 || *cursor < MAX_ERROR_BUFFER))
    return ;
  write(2, buffer, *cursor * sizeof(char));
  *cursor = 0;
}

static void str_to_buffer(char *buffer, const char *s, size_t *cursor)
{
  size_t len;

  len = ft_strlen(s);
  if (*cursor + len >= MAX_ERROR_BUFFER)
  {
    write(2, buffer, *cursor * sizeof(char));
    *cursor = 0;
  }
  memcpy(buffer + *cursor, s, sizeof(char) * len);
  *cursor += len;
}

int mach_o_error(int code, const char *fmt, ...)
{
    char    error_buffer[MAX_ERROR_BUFFER];
    size_t  i;
    size_t  cursor;
    va_list arg;
    
    memset(error_buffer, 0, sizeof(char) * MAX_ERROR_BUFFER);
    if (!fmt)
    {
      getcwd(error_buffer, MAX_ERROR_BUFFER);
      if (errno == 0)
      {
        memcpy(error_buffer + ft_strlen(error_buffer),
        ": The file was not recognized as a valid object file\n",
        ft_strlen(": The file was not recognized as a valid object file\n") * sizeof(char));
        write(2, error_buffer, ft_strlen(error_buffer) * sizeof(char));
      }
      else
        perror(error_buffer);
      return (code);
    }
    va_start(arg, fmt);
    i = 0;
    cursor = 0;
    while (fmt[i])
    {
      while (fmt[i] != '%' && fmt[i])
      {
        error_buffer[cursor++] = fmt[i++];
        out_buffer(error_buffer, &cursor, false);
      }
      if (fmt[++i] == 's' && i++)
          str_to_buffer(error_buffer, va_arg(arg, char*), &cursor);
      else
        error_buffer[cursor++] = fmt[i++];
    }
    out_buffer(error_buffer, &cursor, true);
    va_end(arg);
    return (code);
} 

