.intel_syntax noprefix

.section .rodata
    
    x: .long 0,1,1,0,0,1,2,2,2
    y: .long 0,0,1,1,2,2,2,1,0 
.bss  
    originalx: .int 0
    originaly: .int 0
.text
.global peano_meander

peano_meander:
    push rbx
    push rax
    push rsi
    push rdx
    mov r10,rdx
    xor r12,r12 //our counter = 0
    mov r14,16
    mov r13,rdi
    dec r13
    call power
    mov r13,rax
    mov rax,9
    mul r13
    mov r13,rax // r13 has the end loop
    loopmain:
    cmp r13,r12
    je endmain
    mov rcx,r12
    inc r12
    call in_index
    cmp r8,-1
    je loopmain
    mov [r10],r9
    add r10,8
    mov [rsi],r8
    add rsi,8
    jmp loopmain
    endmain:
    pop rdx
    pop rsi
    pop rax
    pop rbx
    ret


// takes number in rcx, returns its coordinates in (r8,r9), returns both -1 if it wasnt legal point
in_index:
    push r12
    push r13
    push r14
    push r15
    push r10
    xor r10,r10
    mov r10,rcx //r10 is our index
    and r10,15
    cmp r10,8
    jg illegal
    push rcx
    xor rcx,rcx
    mov ecx,dword ptr [x+4*r10] //r8,r9 is our original x and y
    mov r8,rcx
    xor rcx,rcx
    mov ecx,dword ptr [y+4*r10]
    mov r9,rcx
    pop rcx
    mov r13,1 //counter for loop
    loop:
    cmp r13,rdi
    je end
    shr rcx,4
    mov r10,rcx
    and r10,15
    mov r14,3
    call power //len saved in rax
    mov r15,rax
    inc r13
    cmp r10,0
    je zerosquare
    cmp r10,1
    je firstsquare
    cmp r10,2
    je secondsquare
    cmp r10,3
    je thirdsquare
    cmp r10,4
    je fourthsquare
    cmp r10,5
    je fifthsquare
    cmp r10,6
    je sixthsquare
    cmp r10,7
    je seventhsquare
    cmp r10,8
    je eigthsquare
    jg illegal
    pop r10
    pop r15
    pop r14
    pop r13
    pop r12
    ret
    

zerosquare:
    jmp loop  

firstsquare:
    mov r11,r8
    mov r8,r9
    mov r9,r11
    add r8,r15
    jmp loop

secondsquare:
    mov r11,r8
    mov r8,r9
    mov r9,r11
    add r8,r15
    add r9,r15
    jmp loop

thirdsquare:
    mov r11,r15
    dec r11
    sub r11,r8
    mov r8,r11
    mov r11,r15
    dec r11
    sub r11,r9
    mov r9,r11
    add r9,r15
    jmp loop   
    
fourthsquare:
    mov r11,r15
    add r11,r15
    add r9,r11
    jmp loop  

fifthsquare:
    mov r11,r15
    add r8,r11
    add r11,r15
    add r9,r11
    jmp loop  

sixthsquare:
    mov r11,r15
    add r11,r15
    add r9,r11
    add r8,r11
    jmp loop  

seventhsquare:
    mov r11,r8 // for x
    mov r8,r9
    mov r9,r11
    mov r11,r15
    dec r11
    sub r11,r8
    mov r8,r11
    mov r11,r15
    add r11,r15
    add r8,r11
    mov r11,r15 //for y
    dec r11
    sub r11,r9
    mov r9,r11
    mov r11,r15
    add r9,r15
    jmp loop  

eigthsquare:
   mov r11,r8 // for x
    mov r8,r9
    mov r9,r11
    mov r11,r15
    dec r11
    sub r11,r8
    mov r8,r11
    mov r11,r15
    add r11,r15
    add r8,r11
    mov r11,r15 //for y
    dec r11
    sub r11,r9
    mov r9,r11     
    jmp loop  

illegal:
    mov r8,-1
    mov r9,-1
    pop r10
    pop r15
    pop r14
    pop r13
    pop r12
    ret
end:
    pop r10
    pop r15
    pop r14
    pop r13
    pop r12
    ret    


// take r14 as base and r13 as power
//returns result in rax

power: //first argument it takes is the base the second is the power return in rax
    push rbx
    push r10
    mov r10,r14
    mov r11,r13
    mov rax,r10
    looppower:
    cmp r11,1
    je endpower
    mul r10
    dec r11
    jmp looppower
    endpower:
    pop r10
    pop rbx
    ret