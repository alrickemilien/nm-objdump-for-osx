#include "mach_o.h"
#include <stdarg.h>

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
    
    ft_memset(error_buffer, 0, sizeof(char) * MAX_ERROR_BUFFER);
    set_prefix_mach_o_error_to_buffer(error_buffer);
    va_start(arg, fmt);
    i = 0;
    cursor = ft_strlen(error_buffer);
    while (fmt[i])
    {
      while (fmt[i] != '%' && fmt[i])
      {
        error_buffer[cursor++] = fmt[i++];
        out_buffer(error_buffer, &cursor, false);
      }
      if (fmt[i] && fmt[++i] == 's' && i++)
          str_to_buffer(error_buffer, va_arg(arg, char*), &cursor);
      else if (fmt[i])
        error_buffer[cursor++] = fmt[i++];
    }
    out_buffer(error_buffer, &cursor, true);
    va_end(arg);
    return (code);
} 

