    // Простое использование переменной
    .intel_syntax noprefix
    .global main
    .text
main:
    mov     qword ptr [var + rip], 500

    mov     rdi, [var + rip]
    call    writei64

    call    finish

var:
    .quad    42

// .byte - 1 байт
// .word - 2 байта
// .int  - 4 байта
// .quad - 8 байт

// byte  1 при обращении к памяти  (mov)
// word
// dword
// qword
