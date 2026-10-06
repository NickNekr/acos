    .intel_syntax noprefix
    .global main
main:
    call    readi64         // прочитали индекс
    // r12 - индекс
    mov     r12, rax


    call    readi64         // читаем новое значение
    // r13 - новое значение
    mov     r13, rax

    // base + index * scale + offset
    // SCALE = 1, 2, 4, 8

    lea     r14, [rip + arr]        // абсолютный адрес массива
    lea     r14, [r14 + r12 * 8]    // абсолютный адрес ячейки

    mov     rdi, [r14]

    call    writei64

    mov     [r14], r13

    jmp     main

fin:
    call    finish

    .data
arr:
    .skip 2000000 * 8               // 200 8-байтных чисел
