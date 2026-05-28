.file "benchmark_assembly.s"
.intel_syntax noprefix


.section .text
.global main
.type main, @function
main:
    // Prologue
    endbr64
    push rbp
    mov rbp, rsp


    xor eax, eax
    xor ecx, ecx

loopstart:
    add eax, 15069
    inc ecx
    cmp ecx, 1000000000
    jl loopstart


    // Return
    xor eax, eax
    leave
    ret
