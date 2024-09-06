; Hello World Program (External file include)
; Compile with: nasm -f elf helloworld-inc.asm
; Link with (64 bit systems require elf_i386 option): ld -m elf_i386 helloworld-inc.o -o helloworld-inc
; Run with: ./helloworld-inc

SECTION .data
msg1    db      'Hello, brave new world!', 0Ah              ; our first message string
msg2    db      'This is how we recycle in NASM.', 0Ah      ; our second message string

SECTION .text
global  _start

_start:

    mov     eax, msg1       ; move the address of our first message string into EAX
    call    sprint          ; call our string printing function

    mov     eax, msg2       ; move the address of our second message string into EAX
    call    sprint          ; call our string printing function

    call    quit            ; call our quit function


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
    push    eax             ; save the pointer to the message in stack
    call    slen            ; get the length of the message in EAX

    mov     edx, eax        ; length of the message in EDX
    pop     eax             ; restore the pointer to the message from stack

    mov     ecx, eax        ; pointer to the message in ECX
    mov     ebx, 1          ; file descriptor 1 is stdout
    mov     eax, 4          ; syscall number (sys_write)
    int     80h

    pop     ebx
    pop     ecx
    pop     edx
    ret


;------------------------------------------
; void quit()
; Exit program
quit:
    mov     eax, 1          ; syscall number (sys_exit)
    xor     ebx, ebx        ; exit code 0
    int     80h
