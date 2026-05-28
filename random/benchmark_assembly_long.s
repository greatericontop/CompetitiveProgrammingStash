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
    add rax, rdx
    inc ecx
    cmp ecx, 1000000000
    jl loopstart


    // Return
    xor eax, eax
    leave
    ret
