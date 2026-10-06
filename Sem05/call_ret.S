    .intel_syntax noprefix
    .global main

//    lea     rax, [rip + hello]
//    push    rax

add_numbers:
    // Текущее состояние стека (слева верх, справа низ)
    // [    return   xxxxx]
    //      ^rsp    
    add     rdi, rax  
    ret

main:
    mov     rdi, 5            
    mov     rax, 6           

    call    add_numbers       

    call    writei64
    call    finish

//hello:
//    mov     rdi, 42            
//    call    writei64
//    call    finish
    
