.intel_syntax noprefix

.section .rodata
    x: .int 0,0,0,1,2,2,1,1,2,-1
    y: .int 0,1,2,2,2,1,1,0,0,-1

   
.bss  
    originalx: .int 0
    originaly: .int 0
    counter: .int 0
    scores: .space 400
.text
.global peano_meander

peano_meander:
    // TODO: trying to copy from data to register and print it in the c file :)
    
    call copythem
    ret



copythem:
    push rsi
    push rdx
    push rcx
    xor r10,r10
    xor rcx,rcx
    xor r11,r11
    loopx:
    mov ecx, dword ptr [x+r10]
    add r10,4
    cmp ecx,-1
    je loopybefore
    mov [rsi+r11],rcx
    add r11,8
    jmp loopx
    
    loopybefore:
    xor rcx,rcx
    xor r10,r10
    xor r11,r11
    loopybegin:
    mov ecx, dword ptr [y+r10]
    add r10,4
    cmp ecx,-1
    je endcopy
    mov [rdx+r11],rcx
    add r11,8
    jmp loopybegin

    endcopy:
    pop rcx
    pop rdx
    pop rsi
    ret



