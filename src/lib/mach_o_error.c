#include "mach_o.h"
#include <errno.h>
#include <limits.h>

static const t_mach_o_error g_macho_error[] = {
  {
    MACH_O_ERROR_INVALID_MAGICK,
    MACH_O_ERROR_INVALID_MAGICK_STR,
  },
  {
    MACH_O_ERROR_INVALID_FILE_SIZE,
    MACH_O_ERROR_INVALID_FILE_SIZE_STR,
  },
  {
    MACH_O_ERROR_INVALID_FILE,
    MACH_O_ERROR_INVALID_FILE_STR,
  },
  {
    MACH_O_ERROR_MAP_LOADING,
    MACH_O_ERROR_MAP_LOADING_STR,
  },
  {
    MACH_O_ERROR_INVALID_MACH_HEADER,
    MACH_O_ERROR_INVALID_MACH_HEADER_STR,
  },
  {
    MACH_O_ERROR_INVALID_FILETYPE,
    MACH_O_ERROR_INVALID_FILETYPE_STR,
  },
  {
    MACH_O_ERROR_INVALID_SYMBOL_TYPE,
    MACH_O_ERROR_INVALID_SYMBOL_TYPE_STR,
  },
  {
    MACH_O_ERROR_INVALID_FILE_TYPE,
    MACH_O_ERROR_INVALID_FILE_TYPE_STR,
  },
  {
    0,
    NULL,
  },
};

// int mach_o_error(int code)
// {
//     size_t i;
//     size_t len;
//     char error_buffer[MAX_ERROR_BUFFER];

//     // No worry when error here, just path missing
//     getcwd(error_buffer, MAX_ERROR_BUFFER);

//     len = ft_strlen(error_buffer);
//     memcpy(error_buffer + len, " : ", 3 * sizeof(char));
//     len += 3;

//     i = 0;
//     while(g_macho_error[i].error != NULL)
//     {
//       if (g_macho_error[i].code == code)
//       {
//         memcpy(error_buffer + len,
//               g_macho_error[i].error,
//               ft_strlen(g_macho_error[i].error) * sizeof(char));
//         len += ft_strlen(g_macho_error[i].error) * sizeof(char);
//         error_buffer[len] = 0;
//         perror(error_buffer);
//         return (-1);
//       }
//       i++;
//     }

//     return (-1);
// }

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

    perror(error_buffer);

    return (-1);
}