
    .intel_syntax noprefix
    .global main

main:
    push    rbp
    mov     rbp, rsp

    // Загрузка данных x и y в xmm0 и xmm1
    // unaligned
    movupd  xmm0, [rip + x]                  // xmm0 = x[0], x[1]
    movupd  xmm1, [rip + y]                  // xmm1 = y[0], y[1]

    // Горизонтальная сумма (haddpd)
    haddpd  xmm0, xmm1
    movhlps xmm1, xmm0

    lea     rdi, [rip + horizontal_format]
    mov     rax, 2
    call    printf

    movupd  xmm0, [rip + x]
    movupd  xmm1, [rip + y]
    addpd   xmm0, xmm1
    movhlps xmm1, xmm0

    lea     rdi, [rip + vertical_format]
    mov     eax, 2
    call    printf

    xor     eax, eax
    mov     rsp, rbp
    pop     rbp
    ret

    .data
x:
    .double 1.1, 2.2
y:
    .double 3.3, 4.4

horizontal_format:
    .string "horizontal: %lf, %lf\n"
vertical_format:
    .string "vertical: %lf, %lf\n"
