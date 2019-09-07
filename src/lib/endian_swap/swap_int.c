#include "mach_o.h"

uint16_t	swap_int16(uint16_t v)
{
	return (((v & 0xff00) >> 8) |
			((v & 0x00ff) << 8));
}

uint32_t	swap_int32(uint32_t v)
{
	return (((v & 0xff000000) >> 24) |
			((v & 0x00ff0000) >> 8) |
			((v & 0x0000ff00) << 8) |
			((v & 0x000000ff) << 24));
}

uint64_t	swap_int64(uint64_t v)
{
	return ((((v & 0xff00000000000000ULL) >> 56) |
			((v & 0x00ff000000000000ULL) >> 40) |
			((v & 0x0000ff0000000000ULL) >> 24) |
			((v & 0x000000ff00000000ULL) >> 8) |
			((v & 0x00000000ff000000ULL) << 8) |
			((v & 0x0000000000ff0000ULL) << 24) |
			((v & 0x000000000000ff00ULL) << 40) |
			((v & 0x00000000000000ffULL) << 56)));
}