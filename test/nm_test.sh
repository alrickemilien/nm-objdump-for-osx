#!/bin/bash

# ./ft_nm nm
echo "./ft_nm nm"
diff <(./ft_nm nm) <(nm nm)

# ./ft_nm empty.txt
#echo "./ft_nm empty.txt"
#touch empty.txt
#diff <(./ft_nm empty.txt) <(nm empty.txt)
#rm empty.txt

# ./ft_nm Makefile
#echo "./ft_nm Makefile"
#diff <(./ft_nm Makefile) <(nm Makefile)

# ./ft_nm /dev/null
#echo "./ft_nm /dev/null"
#diff <(./ft_nm /dev/null) <(nm /dev/null)

# ./ft_nm /usr
#diff <(./ft_nm /usr) <(nm < /usr)

# ./ft_nm
#diff <(./ft_nm) <(nm)

# ./ft_nm /bin/sh /bin/zsh
#diff <(./ft_nm /bin/sh /bin/zsh) <(nm /bin/sh /bin/zsh)

# ./ft_nm | cat /bin/sh
#diff <(./ft_nm | cat /bin/sh) <(nm | cat /bin/sh)

# ./ft_nm | cat -n 3 /bin/sh
#diff <(./ft_nm | cat -n 3 /bin/sh) <(nm | cat -n 3 /bin/sh)

# ./ft_nm < /bin/sh
#diff <(./ft_nm < /bin/sh) <(nm < /bin/sh)

# ./ft_nm /usr/lib/liby.a
#diff <(./ft_nm /usr/lib/liby.a) <(nm /usr/lib/liby.a)

# ./ft_nm /usr/lib/libc.dylib
#diff <(./ft_nm /usr/lib/libc.dylib) <(nm /usr/lib/libc.dylib)

# ./ft_nm /usr/lib/system/libc.dylib /usr/lib/liby.a
#diff <(./ft_nm /usr/lib/system/libc.dylib /usr/lib/liby.a) <(nm /usr/lib/system/libc.dylib /usr/lib/liby.a)

# ./ft_nm /bin/grep
#diff <(./ft_nm /bin/grep) <(nm /bin/grep)

# ./ft_nm /sbin/reboot
#diff <(./ft_nm /sbin/reboot) <(nm /sbin/reboot)

# ./ft_nm file.o
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#diff <(./ft_nm file.o) <(nm file.o)

# nm file.o renamed to .a
#mv file.o file.a
#diff <(./ft_nm file.a) <(nm  file.a)

# nm file.o renamed to .dyld
#mv file.a file.dyld
#diff <(./ft_nm file.dyld) <(nm  file.dyld)

# nm file.o renamed to no point
#mv file.dyld file
#diff <(nm file) <(nm  file)

#rm file.c file


# nm nm
# nm nm && echo $? > real_nm_ret.txt
# ./ft_nm nm && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src
# nm nm src && echo $? > real_nm_ret.txt
# ./ft_nm nm src && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src otool
# nm nm src otool && echo $? > real_nm_ret.txt
# ./ft_nm nm src otool && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt

# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm file with no read permission
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#chmod 000 file.o
#diff <(./ft_nm file.o) <(nm file.o)
#rm file.c file.o
