#include <stdio.h>
#include <string.h>

int fmt_strings() {
    char string[10];
    int A = -73;
    unsigned int B = 31337;
    strcpy(string, "sample");
   
    // Example of printing with different format string
    printf("[A] Dec: %d, Hex: %x, Unsigned: %u\n", A, A, A);
    printf("[B] Dec: %d, Hex: %x, Unsigned: %u\n", B, B, B);
    printf("[field width on B] 3: '%3u', 10: '%10u', '%08u'\n", B, B, B);
    printf("[string] %s Address %08x\n", string, string);
    // Example of unary address operator (dereferencing) and a %x format string
    printf("variable A is at address: %08x\n", &A);
}

int input() {
    
    char message[10];
    int count, i;
    strcpy(message, "Hello, world!");
    printf("Repeat how many times? ");
    scanf("%d", &count);
    for(i=0; i < count; i++)
    printf("%3d - %s\n", i, message);
}

