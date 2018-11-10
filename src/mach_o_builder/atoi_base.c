#include "mach_o_builder.h"

static inline bool is_digit(char c) {
  if (c >= '0' && c <= '9')
    return (true);
  return (false);
}

static inline bool is_alpha_low(char c) {
  if (c >= 'a' && c <= 'z')
    return (true);
  return (false);
}

static inline bool is_alpha_big(char c) {
  if (c >= 'A' && c <= 'Z')
    return (true);
  return (false);
}

static inline bool is_alpha_num(char c) {
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 0 && c <= '9'))
    return (true);
  return (false);
}

/*
** Read 0x2A5F
** start_index is the index of start of the number
** 0F will be 0, 0x0F will be 2
*/
uint64_t atoi_base(const char *str, size_t base)
{
  size_t      start_index;
  size_t      end_index;
  size_t      i;
  uint64_t    ret;
//  const char  *map = "0123456789ABCDEF";

//debug_s("yaaa\n");
//debug("yaaa %s\n", str);

  start_index = 0;
  if (0 == memcmp(str, "0x", sizeof(char) * 2))
    start_index = 2;

//  debug("%s\n", str + start_index);

  end_index = start_index;
  while (str[end_index] && is_alpha_num(str[end_index]))
    end_index++;

  end_index--;

  ret = 0;
  i = 0;
  while (end_index >= start_index) {
  //  debug("end_index : %ld start_index : %ld\n", end_index, start_index);
    if (is_digit(str[end_index]))
      ret += (str[end_index] - '0') * powl(base, i);
    else if (is_alpha_low(str[end_index]))
      ret += (str[end_index] - 'a' + 10) * powl(base, i);
    else if (is_alpha_big(str[end_index]))
      ret += (str[end_index] - 'A' + 10) * powl(base, i);
    else
      return (ret);
    end_index--;
    i++;
  }

  return (ret);
}
