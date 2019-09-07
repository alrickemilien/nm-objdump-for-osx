/*
** Get identifier for cpu
** according to cpu type
*/

#import <mach/machine.h>
#import <stddef.h>

typedef struct s_cpu_type_names {
  cpu_type_t cputype;
  const char *cpu_name;
}               t_cpu_type_names;

static const t_cpu_type_names g_cpu_type_names[] = {
  { CPU_TYPE_I386, "i386" },
  { CPU_TYPE_X86_64, "x86_64" },
  { CPU_TYPE_ARM, "arm" },
  { CPU_TYPE_ARM64, "arm64" },
  { 0, NULL }
};

const char *cpu_type_name(cpu_type_t cpu_type)
{
  size_t  i;

  i = 0;
  while (g_cpu_type_names[i].cpu_name != NULL)
  {
    if (cpu_type == g_cpu_type_names[i].cputype)
      return (g_cpu_type_names[i].cpu_name);

    i++;
  }

  return "unknown";
}