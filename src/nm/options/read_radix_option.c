#include "nm.h"

typedef struct s_radix_option {
    char        *name;
    int         value;
}               t_radix_option;

t_radix_option g_radix_options[] = {
    { "o", 8 },
    { "x", 16 },
    { "d", 10 },
    {NULL, -1},
};

/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

static int print_error_radix_option(const char *data)
{
    size_t len;
    char error_buffer[MAX_ERROR_BUFFER];
    char s[] = "for the -radix option: Cannot find the option named '";

    memset(error_buffer, 0, sizeof(char) * MAX_ERROR_BUFFER);

    len = 0;

    // for the part
    memcpy(error_buffer + len, s, ft_strlen(s) * sizeof(char));
    len += ft_strlen(s);

    // option part
    if (data)
    {
        memcpy(error_buffer + len,
            data,
            ft_strlen(data) * sizeof(char));
        len += ft_strlen(data);
    }

    memcpy(error_buffer + len,
        "'.\n",
        ft_strlen("'.\n") * sizeof(char));
    len += ft_strlen("'.\n");

    write(2, error_buffer, len * sizeof(char));

    return (1);
}

int read_radix_option(t_options *options, const char *value)
{
    size_t  i;
    size_t  len;

    if (value[0] == 0)
        return (-1);

    len = ft_strlen(value);
    i = 0;
    while (g_radix_options[i].name != NULL)
    {
        if (ft_strcmp(value, g_radix_options[i].name) == 0
            && ft_strlen(g_radix_options[i].name) == len)
        {
            options->RADIX = g_radix_options[i].value;
            return (0);
        }
        i++;
    }

    print_error_radix_option(value);

    return (-1);
}