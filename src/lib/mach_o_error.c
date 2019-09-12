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

static const char error_buffer[MAX_ERROR_BUFFER];

static void out_buffer(const char *buffer, size_t *cursor)
{
  write(2, buffer, *cursor * sizeof(char));
  *cursor = 0;
}

static void str_to_buffer(const char *buffer, const char *s, size_t *cursor)
{
  size_t len;

  len = ft_strlen(s);
  if (*cursor + len >= MAX_ERROR_BUFFER)
    out_buffer(error_buffer, cursor);
  memcpy(error_buffer + *cursor, s, sizeof(char) * len);
  *cursor += len;
}

int mach_o_error_fmt(int code, const char *fmt, ...) 
{
    char    *s; 
    size_t  i;
    size_t  cursor;
    va_list arg;

    va_start(arg, format);
    i = 0;
    cursor = 0;
    while (fmt[i])
    {
      while (fmt[i] != '%' && fmt[i])
      {
        error_buffer[cursor++] = fmt[i++];
        if (cursor == MAX_ERROR_BUFFER)
          out_buffer(error_buffer, &cursor);
      }
      if (fmt[++i] == 's' && i++)
          str_to_buffer(error_buffer, va_arg(arg, char*), &cursor) 
      else
        error_buffer[cursor++] = fmt[i++];
    }
    if (cursor != 0)
      out_buffer(error_buffer, &cursor);
    va_end(arg);
    return (code);
} 

int mach_o_error(int code, const char *data)
{
    size_t len;
    char error_buffer[MAX_ERROR_BUFFER];

    (void)code;
    (void)g_macho_error;

    memset(error_buffer, 0, sizeof(char) * MAX_ERROR_BUFFER);

    // No worry when error here, just path missing
    getcwd(error_buffer, MAX_ERROR_BUFFER);

    len = ft_strlen(error_buffer);
    memcpy(error_buffer + len, ": ", 2 * sizeof(char));
    len += 2;

    // Data part if any
    if (data)
    {
      memcpy(error_buffer + len, data, ft_strlen(data) * sizeof(char));
      len += ft_strlen(data);
    }

    if (errno == 0)
    {
      memcpy(error_buffer + len, ": The file was not recognized as a valid object file\n", ft_strlen(": The file was not recognized as a valid object file\n") * sizeof(char));
      len += ft_strlen(": The file was not recognized as a valid object file\n");
      write(2, error_buffer, len);
    }
    else
    {
      perror(error_buffer);
    }

    return (-1);
}
