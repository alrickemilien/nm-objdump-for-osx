#include "nm.h"

typedef struct s_arch_option {
    char        *name;
    int         value;
}               t_arch_option;

t_arch_option g_arch_options[] = {
    { "x86_64", 0 },
    { "x86-64", 0 },
    { "i386", 1 },
    { "ppc", 2 },
    {NULL, -1},
};


/*
** Read option like -- or --reverse
** compare name + 2 in order to skip -- from --reverse for example
** When the option does not exist print error and return 0
*/

static int print_error_arch_option(const char *data)
{
    size_t len;
    char error_buffer[MAX_ERROR_BUFFER];
    char s[] = "for the -arch option: Unknown architecture named '";

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

int read_arch_option(t_options *options, const char *value)
{
    size_t  i;
    size_t  len;

    if (value[0] == 0)
        return (-1);

    len = ft_strlen(value);
    i = 0;
    while (g_arch_options[i].name != NULL)
    {
        if (ft_strcmp(value, g_arch_options[i].name) == 0
            && ft_strlen(g_arch_options[i].name) == len)
        {
            options->ARCH_TYPE = g_arch_options[i].value;
            return (0);
        }
        i++;
    }

    print_error_arch_option(value);

    return (-1);
}
