#include "mach_o.h"

uint16_t	ato16u(const char *str)
{
	return (ato16u_base(str, "0123456789"));
}