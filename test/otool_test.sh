#!/bin/bash

# ./ft_otool otool
echo "./ft_otool otool "
diff <(./ft_otool otool ) <(otool -t  otool )

# otool empty.txt
#echo "otool empty.txt"
#touch empty.txt
#diff <(./ft_otool empty.txt) <(otool -t  empty.txt)
#rm empty.txt

# otool Makefile
#echo "otool Makefile"
#diff <(./ft_otool Makefile) <(otool -t  Makefile)

# otool /dev/null
#echo "otool /dev/null"
#diff <(otool /dev/null) <(otool -t  /dev/null)

# otool /usr
#diff <(./ft_otool /usr) <(otool -t  < /usr)

# otool
#diff <(./ft_otool) <(otool -t )

# otool /bin/sh /bin/zsh
#diff <(./ft_otool /bin/sh /bin/zsh) <(otool -t  /bin/sh /bin/zsh)

# otool | cat /bin/sh
#diff <(./ft_otool | cat /bin/sh) <(otool -t  | cat /bin/sh)

# otool | cat -n 3 /bin/sh
#diff <(./ft_otool | cat -n 3 /bin/sh) <(otool -t  | cat -n 3 /bin/sh)

# otool < /bin/sh
#diff <(./ft_otool < /bin/sh) <(otool -t  < /bin/sh)

# otool /usr/lib/liby.a
#diff <(./ft_otool /usr/lib/liby.a) <(otool -t  /usr/lib/liby.a)

# otool /usr/lib/libc.dylib
#diff <(./ft_otool /usr/lib/libc.dylib) <(otool -t  /usr/lib/libc.dylib)

# otool /usr/lib/system/libc.dylib /usr/lib/liby.a
#diff <(./ft_otool /usr/lib/system/libc.dylib /usr/lib/liby.a) <(otool -t  /usr/lib/system/libc.dylib /usr/lib/liby.a)

# otool /bin/grep
#diff <(./ft_otool /bin/grep) <(otool -t  /bin/grep)

# otool /sbin/reboot
#diff <(otool /sbin/reboot) <(otool -t  /sbin/reboot)

# otool file.o
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" > file.c
#gcc file.c -o file.o
#diff <(otool file.o) <(otool -t  file.o)

# otool file.o renamed to .a
#mv file.o file.a
#diff <(./ft_otool file.a) <(otool -t  file.a)

# otool file.o renamed to .dyld
#mv file.a file.dyld
#diff <(./ft_otool file.dyld) <(otool -t  file.dyld)

# otool file.o renamed to no point
#mv file.dyld file
#diff <(./ft_otool file) <(otool -t  file)

#rm file file

# otool otool
# otool -t otool && echo $? > real_otool_ret.txt
# ./ft_otool otool && echo $? > ft_otool_ret.txt
# diff real_otool_ret.txt ft_otool_ret.txt
# rm -rf real_otool_ret.txt ft_otool_ret.txt

# otool otool src
# otool -t otool src && echo $? > real_otool_ret.txt
# ./ft_otool otool src && echo $? > ft_otool_ret.txt
# diff real_otool_ret.txt ft_otool_ret.txt
# rm -rf real_otool_ret.txt ft_otool_ret.txt

# otool otool src otool
# otool -t otool src otool && echo $? > real_otool_ret.txt
# ./ft_otool otool src otool && echo $? > ft_otool_ret.txt
# diff real_otool_ret.txt ft_otool_ret.txt

# rm -rf real_otool_ret.txt ft_otool_ret.txt

# otool file with no read permission
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#chmod 000 file.o
#diff <(./ft_otool file.o) <(otool file.o)
#rm file.c file.o
