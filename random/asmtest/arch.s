.intel_syntax noprefix

.section .text
.globl add
.type add, @function
add:
    endbr64
    // arguments are passed in edi and esi

    // incorrect
    //add rdi, rsi
    //mov rax, rdi

    // correct
    movsxd rdi, edi
    movsxd rsi, esi
    add rdi, rsi
    mov rax, rdi

    ret
