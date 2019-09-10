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

int read_arch_option(t_options *options, const char *value)
{
    size_t  i;
    size_t  len;

    if (value[0] == 0)
        return (-1);

    len = ft_strlen(value);
    while (g_arch_options[i].name != NULL)
    {
        if (ft_strcmp(value, name) == 0
            && ft_strlen(g_arch_options[i].name) == len)
        {
            options->ARCH_TYPE = g_arch_options[i].value;
            return (0);
        }
        i++;
    }

    return (-1);
}
