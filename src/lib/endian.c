#include "mach_o_utils.h"

/*
** LITTLE ENDIAN MEANS LAST BYTE IS STORED AT FIRST
** little                          big
** 0x00 0xF0 0x00 0x00             0x00 0x00 0xF0 0x00
*/

uint64_t endian()
{
  uint64_t one = 1L;

  if (*((uint8_t*)(&one)) == 1)
    return (LITTLE_ENDIAN); // 1000000 00000000 00000000 00000000

  return (BIG_ENDIAN);// 0000000 00000000 00000000 10000000
}
