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


void read_string(const char *value_str, char **buffer)
{
  size_t i;

  i = 0;
  while (value_str && value_str[i] && value_str[i] != '\n')
    i++;

  if (i == 0)
    return ;

  *buffer = (char*)malloc(sizeof(char) * i);

  if (NULL == *buffer)
    return ;

  while (value_str[i] && value_str[i] != '\n')
  {
    (*buffer)[i] = value_str[i];

    i++;
  }
}

/*
** Merge the strings a and b,
** free the both given as pareemeter and return a new one
*/

char *merge_strings(char *s1, char *s2) {
  char      *new_str;
	size_t		i;
	size_t		j;

	new_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));

  if (NULL == new_str)
		return (NULL);

  j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[j] = s1[i];
		i++;
		j++;
	}

  i = 0;
	while (s2[i] != '\0')
	{
		new_str[j] = s2[i];
		i++;
		j++;
	}

  free(s1);
  free(s2);

	return (new_str);
}
