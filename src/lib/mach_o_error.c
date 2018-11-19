#include "mach_o_utils.h"

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
    MACH_O_ERROR_INVALID_FILE_TYPE,
    MACH_O_ERROR_INVALID_FILE_TYPE_STR,
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
    0,
    NULL,
  },
};

int mach_o_error(int code)
{
    int i;

    i = 0;
    while(g_macho_error[i].error != NULL)
    {
      if (g_macho_error[i].code == code)
      {
        ft_putendl_fd(g_macho_error[i].error, 2);
        return (-1);
      }
      i++;
    }

    return (-1);
}
