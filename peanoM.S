.intel_syntax noprefix

.section .rodata
    
    x: .long 0,0,0,1,2,2,1,1,2
    y: .long 0,1,2,2,2,1,1,0,0 
.text
.global peano_meander

peano_meander:
    mov r10,rdx
    cmp rdi,1
    je onlyfirst
    push rbx
 //pushing the calee saved registers cause i used them
    mov r14,3 //calculating how many time to loop
    mov rax,rdi
    shl rax,1
    mov r13,rax  
    call power
    mov r12,rax  //r12 has now number of all points which is 3^(2*n)
    dec r12 //r12 numbers we DONT NEED
    xor rcx,rcx //numbers we NEED
    loopmain: //here starts our algorithm for jumping over numbers that we dont need
    cmp r12,-1
    je endmain
    continue:
    mov r11,rcx
    xor r13,r13
    checkfirstfour: //we find the 4 bits where we can still add 1
    mov rbx,r11
    and rbx,0x8
    cmp rbx,0 
    jle ifstat
    inc r13 //and save how many 4 bits we moved in r13
    shr r11,4
    jmp checkfirstfour
    ifstat: //here we check if we can fit in our first 4 bit one more number
    cmp r13,0
    jne contloop    
    call in_index //if yes, we find our point in this specific index
    mov [r10],r9
    add r10,8
    mov [rsi],r8
    add rsi,8
    dec r12
    inc rcx
    jmp loopmain
    contloop:
    call in_index //if we cant fit, then we already have 8 in first 4 bits,so we cann it on this index
    mov [r10],r9
    add r10,8
    mov [rsi],r8
    add rsi,8
    shl r13,2
    mov rax,r13
    push r15
    mov r15,rcx
    mov rcx,rax
    shr r15,cl  //shifted left 4*n (num of bits) till we get to 4 bits which are less than 8
    inc r15
    shl r15,cl //filled cl bits with 9 to startover after i incremented our first 4 bits
    mov rcx,r15
    pop r15
    dec r12
    jmp loopmain
    endmain:
    pop rbx
    ret


// takes number in rcx, returns its coordinates in (r8,r9), returns both -1 if it wasnt legal point
in_index:
    push rcx
    push r12
    push r13
    push r15
    push r10
    xor r10,r10
    mov r10,rcx //r10 is our index
    and r10,15
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
    cmp r10,0 //looking which square do we need
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
    pop r10
    pop r15
    pop r13
    pop r12
    pop rcx
    ret
    
onlyfirst: //when the user enters 1, it comes here and copied from the .rodata that we have
    mov r11,0
    xor rcx,rcx

    loopcopy:
    cmp r11,9
    je endcopy
    mov ecx,dword ptr [x+4*r11]
    mov [rsi],rcx
    xor rcx,rcx
    mov ecx,dword ptr [y+4*r11]
    mov [r10],rcx
    inc r11
    add rsi,8
    add r10,8
    jmp loopcopy

    endcopy:
    ret

//all the squares with its own offsets
zerosquare:
    xchg r8,r9
    jmp loop  

firstsquare:
    xchg r8,r9
    add r9,r15
    jmp loop

secondsquare:
    lea r9,[r9+2*r15]
    jmp loop

thirdsquare:
    add r8,r15
    lea r9,[r9+2*r15]
    jmp loop


fourthsquare:
    lea r8,[r8+2*r15]
    lea r9,[r9+2*r15]
    jmp loop




fifthsquare:
    mov r11,r15
    dec r11
    sub r11,r8
    mov r8,r11
    lea r8,[r8+2*r15]
    mov r11,r15
    dec r11
    sub r11,r9
    mov r9,r11
    add r9,r15
    jmp loop  

sixthsquare:
    xchg r8,r9
    lea r11,[2*r15]
    dec r11
    sub r11,r8
    mov r8,r11
    lea r11,[2*r15]
    dec r11
    sub r11,r9
    mov r9,r11
    jmp loop  

seventhsquare:
    xchg r8,r9
    lea r11,[2*r15]
    dec r11
    sub r11,r8
    mov r8,r11
    mov r11,r15
    dec r11
    sub r11,r9
    mov r9,r11
    jmp loop   

eigthsquare:
    lea r8,[r8+2*r15]    
    jmp loop  

// end of squares
end:
    pop r10
    pop r15
    pop r13
    pop r12
    pop rcx
    ret    


// take r14 as base and r13 as power
//returns result in rax

power: //first argument it takes is the base the second is the power return in rax
    cmp r13,0
    je endnull
    push r11
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
    pop r11
    ret
    
    endnull:
    mov rax,1
    ret
