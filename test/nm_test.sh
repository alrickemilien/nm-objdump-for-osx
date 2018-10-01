#!/bin/bash

# ./nm nm
echo "./nm nm"
diff <(./nm nm) <(nm nm)

# ./nm empty.txt
#echo "./nm empty.txt"
#touch empty.txt
#diff <(./nm empty.txt) <(nm empty.txt)
#rm empty.txt

# ./nm Makefile
#echo "./nm Makefile"
#diff <(./nm Makefile) <(nm Makefile)

# ./nm /dev/null
#echo "./nm /dev/null"
#diff <(./nm /dev/null) <(nm /dev/null)

# ./nm /usr
#diff <(./nm /usr) <(nm < /usr)

# ./nm
#diff <(./nm) <(nm)

# ./nm /bin/sh /bin/zsh
#diff <(./nm /bin/sh /bin/zsh) <(nm /bin/sh /bin/zsh)

# ./nm | cat /bin/sh
#diff <(./nm | cat /bin/sh) <(nm | cat /bin/sh)

# ./nm | cat -n 3 /bin/sh
#diff <(./nm | cat -n 3 /bin/sh) <(nm | cat -n 3 /bin/sh)

# ./nm < /bin/sh
#diff <(./nm < /bin/sh) <(nm < /bin/sh)

# ./nm /usr/lib/liby.a
#diff <(./nm /usr/lib/liby.a) <(nm /usr/lib/liby.a)

# ./nm /usr/lib/libc.dylib
#diff <(./nm /usr/lib/libc.dylib) <(nm /usr/lib/libc.dylib)

# ./nm /usr/lib/system/libc.dylib /usr/lib/liby.a
#diff <(./nm /usr/lib/system/libc.dylib /usr/lib/liby.a) <(nm /usr/lib/system/libc.dylib /usr/lib/liby.a)

# ./nm /bin/grep
#diff <(./nm /bin/grep) <(nm /bin/grep)

# ./nm /sbin/reboot
#diff <(./nm /sbin/reboot) <(nm /sbin/reboot)

# ./nm file.o
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#diff <(./nm file.o) <(nm file.o)

# nm file.o renamed to .a
#mv file.o file.a
#diff <(./nm file.a) <(nm  file.a)

# nm file.o renamed to .dyld
#mv file.a file.dyld
#diff <(./nm file.dyld) <(nm  file.dyld)

# nm file.o renamed to no point
#mv file.dyld file
#diff <(nm file) <(nm  file)

#rm file.c file


# nm nm
# nm nm && echo $? > real_nm_ret.txt
# ./nm nm && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src
# nm nm src && echo $? > real_nm_ret.txt
# ./nm nm src && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src otool
# nm nm src otool && echo $? > real_nm_ret.txt
# ./nm nm src otool && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt

# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm file with no read permission
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#chmod 000 file.o
#diff <(./nm file.o) <(nm file.o)
#rm file.c file.o
