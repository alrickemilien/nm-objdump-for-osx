#include "mach_o.h"

/*
** /path/to/binary => binary
** binary => binary
*/

static char *extract_binary_name_from_path(char *argv_0)
{
	size_t	i;

	i = ft_strlen(argv_0);
	while (i != 0 && argv_0[i] != '/')
		i--;
	return (argv_0 + i);
}

void 	init_prefix_error(char *argv_0)
{
	char	buffer[MAX_ERROR_BUFFER];
	char	*argv_0_extracted;
    size_t	cwd_len;
    size_t	argv_0_len;

	argv_0_extracted = extract_binary_name_from_path(argv_0);
	ft_memset(buffer, 0, MAX_ERROR_BUFFER);
	getcwd(buffer, MAX_ERROR_BUFFER);
	cwd_len = ft_strlen(buffer);
	argv_0_len = ft_strlen(argv_0_extracted);
	if (argv_0_len >= MAX_ERROR_BUFFER - cwd_len)
	{
		ft_memset(buffer, 0, MAX_ERROR_BUFFER);
		memcpy(buffer, argv_0_extracted, argv_0_len);
	}
	else
		memcpy(buffer + cwd_len, argv_0_extracted, argv_0_len);
	cwd_len = ft_strlen(buffer);
	memcpy(buffer + cwd_len, ": ", 2 * sizeof(char));	
	init_prefix_mach_o_error(buffer);
}