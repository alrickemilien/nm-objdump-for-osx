#include "mach_o_builder.h"

/*
** Remove blank chars arround each word of the given array of word
*/

void trim_each_string_of_array(char **arr)
{
  size_t   i;
  char  *tmp;

  i = 0;
  while (arr[i])
  {
    tmp = ft_strtrim(arr[i]);

    free(arr[i]);

    arr[i] = tmp;

    i++;
  }
}

/*
** Realease the memory of an array of char*
*/

void clear_array(char **arr)
{
  size_t   i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);

    i++;
  }

  free(arr);
}
