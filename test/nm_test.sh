#!/bin/bash

echo_test() {
    echo "TEST: $@"
}

# ./build/ft_nm nm
echo_test "./build/ft_nm donotexist"
diff <(./build/ft_nm donotexist) <(nm donotexist)

# ./build/ft_nm empty.txt
echo_test "./build/ft_nm empty.txt"
touch empty.txt
diff <(./build/ft_nm empty.txt) <(nm empty.txt)
rm empty.txt

# ./build/ft_nm Makefile
#echo "./build/ft_nm Makefile"
#diff <(./build/ft_nm Makefile) <(nm Makefile)

# ./build/ft_nm /dev/null
#echo "./build/ft_nm /dev/null"
#diff <(./build/ft_nm /dev/null) <(nm /dev/null)

# ./build/ft_nm /usr
#diff <(./build/ft_nm /usr) <(nm < /usr)

# ./build/ft_nm
#diff <(./build/ft_nm) <(nm)

# ./build/ft_nm /bin/sh /bin/zsh
#diff <(./build/ft_nm /bin/sh /bin/zsh) <(nm /bin/sh /bin/zsh)

# ./build/ft_nm | cat /bin/sh
#diff <(./build/ft_nm | cat /bin/sh) <(nm | cat /bin/sh)

# ./build/ft_nm | cat -n 3 /bin/sh
#diff <(./build/ft_nm | cat -n 3 /bin/sh) <(nm | cat -n 3 /bin/sh)

# ./build/ft_nm < /bin/sh
#diff <(./build/ft_nm < /bin/sh) <(nm < /bin/sh)

# ./build/ft_nm /usr/lib/liby.a
#diff <(./build/ft_nm /usr/lib/liby.a) <(nm /usr/lib/liby.a)

# ./build/ft_nm /usr/lib/libc.dylib
#diff <(./build/ft_nm /usr/lib/libc.dylib) <(nm /usr/lib/libc.dylib)

# ./build/ft_nm /usr/lib/system/libc.dylib /usr/lib/liby.a
#diff <(./build/ft_nm /usr/lib/system/libc.dylib /usr/lib/liby.a) <(nm /usr/lib/system/libc.dylib /usr/lib/liby.a)

# ./build/ft_nm /bin/grep
#diff <(./build/ft_nm /bin/grep) <(nm /bin/grep)

# ./build/ft_nm /sbin/reboot
#diff <(./build/ft_nm /sbin/reboot) <(nm /sbin/reboot)

# ./build/ft_nm file.o
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#diff <(./build/ft_nm file.o) <(nm file.o)

# nm file.o renamed to .a
#mv file.o file.a
#diff <(./build/ft_nm file.a) <(nm  file.a)

# nm file.o renamed to .dyld
#mv file.a file.dyld
#diff <(./build/ft_nm file.dyld) <(nm  file.dyld)

# nm file.o renamed to no point
#mv file.dyld file
#diff <(nm file) <(nm  file)

#rm file.c file


# nm nm
# nm nm && echo $? > real_nm_ret.txt
# ./build/ft_nm nm && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src
# nm nm src && echo $? > real_nm_ret.txt
# ./build/ft_nm nm src && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt
# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm nm src otool
# nm nm src otool && echo $? > real_nm_ret.txt
# ./build/ft_nm nm src otool && echo $? > ft_nm_ret.txt
# diff real_nm_ret.txt ft_nm_ret.txt

# rm -rf real_nm_ret.txt ft_nm_ret.txt

# nm file with no read permission
#echo "#include<stdio.h>
#int main(){char*a=\"#include<stdio.h>%cint main(){char*a=%c%s%c;printf(a,10,34,a,34);}\";printf(a,10,34,a,34);}" >> file.c
#gcc file.c -o file.o
#chmod 000 file.o
#diff <(./build/ft_nm file.o) <(nm file.o)
#rm file.c file.o
