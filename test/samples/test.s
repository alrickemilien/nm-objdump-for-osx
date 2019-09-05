; comment
default rel
section .data
fmt: db "; comment%2$cdefault rel%2$csection .data%2$cfmt: db %3$c%1$s%3$c, 0%2$csection .text%2$cglobal _main%2$cextern _printf%2$cfunc:%2$clea rdi, [rel fmt]%2$clea rsi, [rel fmt]%2$cmov rdx, 0x0A%2$cmov rcx, 0x22%2$cxor rax, rax%2$ccall _printf%2$cret%2$c_main:%2$c; comment2%2$ccall func%2$cret%2$c", 0
section .text
global _main
extern _printf
func:
lea rdi, [rel fmt]
lea rsi, [rel fmt]
mov rdx, 0x0A
mov rcx, 0x22
xor rax, rax
call _printf
ret
_main:
; comment2
call func
ret
