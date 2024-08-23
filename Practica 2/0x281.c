// simplenote

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void usage(char *prog_name, char *filename) {
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(0);
}

void fatal(char *); // A function for fatal errors
void *ec_malloc(unsigned int); // An error-checked malloc() wrapper

int main(int argc, char *argv[]) {
    int fd; // file descriptor
    char *buffer, *datafile;
    
    buffer = (char *) ec_malloc(100);
    datafile = (char *) ec_malloc(20);
    
    strcpy(datafile, "/tmp/notes");
    
    if(argc < 2) // If there aren't command-line arguments,
        usage(argv[0], datafile); // display usage message and exit.
    
    strcpy(buffer, argv[1]); // Copy into buffer.
    
    printf("[DEBUG] buffer @ %p: '%s'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: '%s'\n", datafile, datafile);
    
    strncat(buffer, "\n", 1); // Add a newline at the end.

    // Opening file
    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    
    if(fd == -1)
        fatal("in main() while opening file");
    
    printf("[DEBUG] file descriptor is %d\n", fd);
    
    // Writing data
    if(write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main() while writing buffer to file");
    
    // Closing file
    if(close(fd) == -1)
        fatal("in main() while closing file");
    
    printf("Note has been saved.\n");
    
    free(buffer);
    free(datafile);
}

// A function to display an error message and then exit
void fatal(char *message) {
    char error_message[100];
    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    
    return ptr;
}

// bitwise

#include <stdio.h>

int main() {
    int i, bit_a, bit_b;
    
    printf("bitwise OR operator |\n");
    for(i = 0; i < 4; i++) {
        bit_a = (i & 2) / 2; // Get the second bit.
        bit_b = (i & 1); // Get the first bit.
        printf("%d | %d = %d\n", bit_a, bit_b, bit_a | bit_b);
    }
    
    printf("\nbitwise AND operator &\n");
    for(i = 0; i < 4; i++) {
        bit_a = (i & 2) / 2; // Get the second bit.
        bit_b = (i & 1); // Get the first bit.
        printf("%d & %d = %d\n", bit_a, bit_b, bit_a & bit_b);
    }
}

// fcntl_flags

#include <stdio.h>
#include <fcntl.h>

void display_flags(char *, unsigned int);
void binary_print(unsigned int);

int main(int argc, char *argv[]) {
    display_flags("O_RDONLY\t\t", O_RDONLY);
    display_flags("O_WRONLY\t\t", O_WRONLY);
    display_flags("O_RDWR\t\t\t", O_RDWR);
    printf("\n");
    display_flags("O_APPEND\t\t", O_APPEND);
    display_flags("O_TRUNC\t\t\t", O_TRUNC);
    display_flags("O_CREAT\t\t\t", O_CREAT);
    printf("\n");
    display_flags("O_WRONLY | O_APPEND | O_CREAT", O_WRONLY | O_APPEND | O_CREAT);
}

void display_flags(char *label, unsigned int value) {
    printf("%s\t: %d\t:", label, value);
    binary_print(value);
    printf("\n");
}

void binary_print(unsigned int value) {
    unsigned int mask = 0xff000000; // Start with a mask for the highest byte.
    unsigned int shift = 256*256*256; // Start with a shift for the highest byte.
    unsigned int byte, byte_iterator, bit_iterator;
    
    for(byte_iterator = 0; byte_iterator < 4; byte_iterator++) {
        byte = (value & mask) / shift; // Isolate each byte.
        printf(" ");
        for(bit_iterator = 0; bit_iterator < 8; bit_iterator++) { // Print the byte's bits.
            if(byte & 0x80) // If the highest bit in the byte isn't 0,
                printf("1"); // print a 1.
            else
                printf("0"); // Otherwise, print a 0.
            byte *= 2; // Move all the bits to the left by 1.
        }
        mask /= 256; // Move the bits in mask right by 8.
        shift /= 256; // Move the bits in shift right by 8.
    }
}


