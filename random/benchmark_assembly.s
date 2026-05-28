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
    mov edx, 21450231

loopstart:
    // Reduce the effect of pipelining by unrolling loop
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    add eax, edx
    inc ecx
    cmp ecx, 100000000
    jl loopstart


    // Return
    xor eax, eax
    leave
    ret
