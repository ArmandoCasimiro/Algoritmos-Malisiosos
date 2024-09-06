; Hello World Program (Passing arguments from the command line)
; Compile with: nasm -f elf helloworld-args.asm
; Link with (64 bit systems require elf_i386 option): ld -m elf_i386 helloworld-args.o -o helloworld-args
; Run with: ./helloworld-args

SECTION .text
global  _start
 
_start:
 
    mov     ecx, 0          ; ecx is initalised to zero.
 
nextNumber:
    inc     ecx             ; increment ecx
 
    mov     eax, ecx        ; move the address of our integer into eax
    add     eax, 48         ; add 48 to our number to convert from integer to ascii for printing
    push    eax             ; push eax to the stack
    mov     eax, esp        ; get the address of the character on the stack
    call    sprintLF        ; call our print function
 
    pop     eax             ; clean up the stack so we don't have unneeded bytes taking up space
    cmp     ecx, 10         ; have we reached 10 yet? compare our counter with decimal 10
    jne     nextNumber      ; jump if not equal and keep counting
 
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
    push    eax         ; push the linefeed onto the stack so we can get the address
    mov     eax, esp    ; move the address of the current stack pointer into eax for sprint
    call    sprint      ; call our sprint function
    pop     eax         ; remove our linefeed character from the stack
    pop     eax         ; restore the original value of eax before our function was called
    ret                 ; return to our program

;------------------------------------------
; void quit()
; Exit program
quit:
    mov     eax, 1          ; syscall number (sys_exit)
    xor     ebx, ebx        ; exit code 0
    int     80h
