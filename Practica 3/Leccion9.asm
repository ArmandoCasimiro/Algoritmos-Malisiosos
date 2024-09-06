; Hello World Program (Passing arguments from the command line)
; Compile with: nasm -f elf helloworld-args.asm
; Link with (64 bit systems require elf_i386 option): ld -m elf_i386 helloworld-args.o -o helloworld-args
; Run with: ./helloworld-args

SECTION .data
msg1        db      'Please enter your name: ', 0Ah, 0    ; message string asking user for input
msg2        db      'Hello, ', 0                         ; message string to use after user has entered their name

SECTION .bss
sinput:     resb    255                                  ; reserve a 255 byte space in memory for the users input string

SECTION .text
global  _start

_start:

    mov     eax, msg1            ; move the address of msg1 into EAX
    call    sprintLF             ; call sprintLF to print msg1 with a newline

    ; Leer la entrada del usuario
    mov     edx, 255             ; number of bytes to read
    mov     ecx, sinput          ; reserved space to store our input (known as a buffer)
    mov     ebx, 0               ; read from the STDIN file
    mov     eax, 3               ; invoke SYS_READ (kernel opcode 3)
    int     80h                  ; interrupt to perform system call

    ; Limpiar el caracter de nueva línea (si es necesario)
    mov     ecx, sinput          ; point to the input buffer
remove_newline:
    cmp     byte [ecx], 0        ; check for null terminator
    je      after_trim           ; if found, exit loop
    cmp     byte [ecx], 0Ah      ; check for newline
    jne     continue_trim        ; if not newline, continue
    mov     byte [ecx], 0        ; replace newline with null terminator
    jmp     after_trim
continue_trim:
    inc     ecx
    jmp     remove_newline

after_trim:
    ; Imprimir el saludo con el nombre del usuario
    mov     eax, msg2            ; move the address of msg2 into EAX
    call    sprint               ; call sprint to print msg2

    mov     eax, sinput          ; move the address of user input into EAX
    call    sprint               ; call sprint to print user input

    call    quit                 ; exit the program

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
