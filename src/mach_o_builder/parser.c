#include "mach_o_builder.h"

static const char *mach_header_keys_map_g[] = {
  "magic_number",
  "cputype",
  "cpusubtype",
  "filetype",
  "ncmds",
  "sizeofcmds",
  "flags",
  "reserved",
  NULL,
};

static const char *section_keys_map_g[] = {
  "section_type",
  "sectname[16]",
  "segname[16]",
  "addr",
  "size",
  "offset",
  "align",
  "reloff",
  "nreloc",
  "flags",
  "reserved1",
  "reserved2",
  NULL,
};

/*
** Check if the property is valid
*/

static bool check_property(const char **arr)
{
  int i;

  // When it's a comment
  if (arr[0][0] == '#')
    return (true);

  i = 0;
  while(*arr) {
    arr++;
    i++;
  }

  if (i != 3)
    return (false);

  return (true);

}

static bool find_valid_key(char *str)
{
  int i;
  int j;

  const char **map[] = {
    section_keys_map_g,
    mach_header_keys_map_g,
    NULL,
  };

  i = 0;
  while(map[i])
  {
    j = 0;
    while (map[i][j])
    {
      if (!ft_strcmp(section_keys_map_g[i], str))
        return (true);
      j++;
    }
    i++;
  }

  return (false);
}

/*
** Remove blank chars arround each word of the given array of word
*/

static void trim_each_string_of_array(char **arr)
{
  int   i;
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

static void clear_array(char **arr)
{
  int   i;

  i = 0;
  while (arr[i])
  {
    free(arr[i]);

    i++;
  }

  free(arr);
}

int build_mach_o_from_conf(const char *path)
{
	int		fd;
	char	*line;
  char  **property;

	fd = load_file_descriptor(path);

	if (fd == -1)
		return (EXIT_FAILURE);

	while(get_next_line(fd, &line) > 0)
	{
		property = ft_strsplit(line, '=');

    trim_each_string_of_array(property);

    if (check_property((const char**)property) == false) {
      printf("Invalid property %s\n", line);
    } else if (find_valid_key(property[0]) == false) {
      printf("Skip %s\n", property[0]);
    }

    clear_array(property);
    free(line);
	}


	return (0);
}
