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


    xor rax, rax
    xor ecx, ecx
    mov rdx, 1753428593230423

loopstart:
    // Reduce the effect of pipelining by unrolling loop
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    add rax, rdx
    inc ecx
    cmp ecx, 100000000
    jl loopstart


    // Return
    xor eax, eax
    leave
    ret
