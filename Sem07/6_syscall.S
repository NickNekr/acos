    #include <sys/syscall.h>

    .intel_syntax noprefix
    .global main
main:
    // SYS_exit = 60 
    // SYS_write = 1 

    // Номер системного вызова передается в rax
    // армументы в rdi, rsi, rdx, r10, r8, r9
    // _exit(4)
    // mov     rax, SYS_exit
    // mov     rdi, 4
    // syscall

    mov     rax, SYS_write
    mov     rdi, 1
    lea     rsi, [rip + hello_world_out]
    mov     rdx, hello_world_end_out - hello_world_out
    syscall

    mov     rax, SYS_write
    mov     rdi, 2
    lea     rsi, [rip + hello_world_err]
    mov     rdx, hello_world_end_err - hello_world_err
    syscall

hello_world_out:
    .ascii  "Hello World STDOUT!\n"
hello_world_end_out:

hello_world_err:
    .ascii  "Hello World STDERR!\n"
hello_world_end_err:
