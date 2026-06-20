.intel_syntax noprefix

.section .rodata
mystring:
    .ascii "Hello, World!\n"
mystring_end:

.section .text
.globl main
.type main, @function
main:
    endbr64
    push rbp
    mov rbp, rsp

    mov eax, 1  # write
    mov rdi, 1  # stdout
    lea rsi, mystring[rip]
    mov rdx, mystring_end - mystring
    syscall

    xor eax, eax

    leave
    ret
