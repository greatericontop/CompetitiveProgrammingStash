.intel_syntax noprefix

.section .rodata
scan_format:
    .ascii "%d %d"
print_format:
    .ascii "The sum of your numbers is %d :yayy:\n"

.section .text
.globl main
.type main, @function
main:
    endbr64
    push rbp
    mov rbp, rsp
    # Allocate space on the stack for two integers
    # They only take 8 bytes, but rsp must be 16-byte aligned
    sub rsp, 16

    # "%d %d"
    lea rdi, scan_format[rip]
    # &var1
    lea rsi, [rbp-4]
    # &var2
    lea rdx, [rbp-8]
    # eax must be zeroed for variadic functions
    # The xor idiom is more popular than mov eax, 0
    xor eax, eax
    # scanf("%d %d", &var1, &var2)
    call scanf

    # "The sum of your numbers is %d :yayy:\n"
    lea rdi, print_format[rip]
    # var1 + var2, in esi
    # The DWORD PTR is optional here because it's obvious that we're loading 32 bits.
    # However, in other cases it may be required.
    mov esi, [rbp-4]  # esi = var1
    mov eax, [rbp-8]  # eax = var2
    add esi, eax  # esi = var1 + var2
    # eax must be zeroed for variadic functions
    xor eax, eax
    # printf("The sum of your numbers is %d :yayy:\n", var1 + var2)
    call printf

    xor eax, eax
    leave
    ret
