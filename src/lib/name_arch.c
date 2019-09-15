#include "mach_o.h"

typedef struct s_arch_map {
    const char  *name;
    int         value;
}               t_arch_map;

t_arch_map g_arch_map[] = {
    { "x86_64", CPU_TYPE_X86_64 },
    { "x86-64", CPU_TYPE_X86_64 },
    { "i386", CPU_TYPE_I386 },
    { "ABI64", CPU_ARCH_ABI64 },
    { "ppc", CPU_TYPE_POWERPC },
    { "", -1 },
};

static const char *g_default_name = "";

const char *name_arch(int arch_type)
{
    size_t  i;

    i = 0;
    while (i * sizeof(t_arch_map) < sizeof(g_arch_map))
    {
        if (g_arch_map[i].value == arch_type)
            return (g_arch_map[i].name);
        i++;
    }
    return (g_default_name);
}