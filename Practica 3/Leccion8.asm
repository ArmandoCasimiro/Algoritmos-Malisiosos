; Hello World Program (Passing arguments from the command line)
; Compile with: nasm -f elf helloworld-args.asm
; Link with (64 bit systems require elf_i386 option): ld -m elf_i386 helloworld-args.o -o helloworld-args
; Run with: ./helloworld-args
 
SECTION .text
global  _start
 
_start:
 
    pop     ecx             ; first value on the stack is the number of arguments
 
nextArg:
    cmp     ecx, 0h         ; check to see if we have any arguments left
    jz      noMoreArgs      ; if zero flag is set jump to noMoreArgs label (jumping over the end of the loop)
    pop     eax             ; pop the next argument off the stack
    call    sprintLF        ; call our print with linefeed function
    dec     ecx             ; decrease ecx (number of arguments left) by 1
    jmp     nextArg         ; jump to nextArg label
 
noMoreArgs:
    call    quit

;------------------------------------------
; int slen(String message)
; String length calculation function
slen:
    push    ebx
    mov     ebx, eax
 
nextchar:
    cmp     byte [eax], 0
    jz      finished
    inc     eax
    jmp     nextchar
 
finished:
    sub     eax, ebx
    pop     ebx
    ret
 
 
;------------------------------------------
; void sprint(String message)
; String printing function
sprint:
    push    edx
    push    ecx
    push    ebx
    push    eax
    call    slen
 
    mov     edx, eax
    pop     eax
 
    mov     ecx, eax
    mov     ebx, 1
    mov     eax, 4
    int     80h
 
    pop     ebx
    pop     ecx
    pop     edx
    ret
 
 
;------------------------------------------
; void sprintLF(String message)
; String printing with line feed function
sprintLF:
    call    sprint
 
    push    eax         ; push eax onto the stack to preserve it while we use the eax register in this function
    mov     eax, 0Ah    ; move 0Ah into eax - 0Ah is the ascii character for a linefeed
                        ; as eax is 4 bytes wide, it now contains 0000000Ah
    push    eax         ; push the linefeed onto the stack so we can get the address
                        ; given that we have a little-endian architecture, eax register bytes are stored in reverse order,
                        ; this corresponds to stack memory contents of 0Ah, 0h, 0h, 0h,
                        ; giving us a linefeed followed by a NULL terminating byte
    mov     eax, esp    ; move the address of the current stack pointer into eax for sprint
    call    sprint      ; call our sprint function
    pop     eax         ; remove our linefeed character from the stack
    pop     eax         ; restore the original value of eax before our function was called
    ret                 ; return to our program
 
 
;------------------------------------------
; void exit()
; Exit program and restore resources
quit:
    mov     ebx, 0
    mov     eax, 1
    int     80h
    ret