.intel_syntax noprefix

.data
    x: .int 0,1,2,2,2,1,1,0,0
    y: .int 0,0,0,1,2,2,1,1,2
.global peano_meander
.text

peano_meander:
    // TODO: trying to copy from data to register and print it in the c file :)
    xor rbx,rbx
    mov bx, word ptr [x]
    mov [rsi],rbx
    xor rbx,rbx
    mov bx, word ptr [x+8]
    add rsi,16
    mov [rsi], rbx
    xor eax, eax
    ret

