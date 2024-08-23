// uid_demo

#include <stdio.h>
#include <unistd.h> 

int main() {
    printf("real uid: %d\n", getuid());
    printf("effective uid: %d\n", geteuid());

    return 0; 
}


// hacking

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal(char *message) {
    char error_message[100];
    strncpy(error_message, "[!!] Fatal Error ", sizeof(error_message) - 1); 
    strncat(error_message, message, sizeof(error_message) - strlen(error_message) - 1); 
    perror(error_message);
    exit(-1);
}

void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}

// notetaker

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

void usage(char *prog_name, char *filename) {
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(0);
}

void fatal(char *);
void *ec_malloc(unsigned int);

int main(int argc, char *argv[]) {
    int userid, fd;
    char *buffer, *datafile;

    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);

    strncpy(datafile, "/var/notes", 19); 

    if(argc < 2)
        usage(argv[0], datafile);

    strncpy(buffer, argv[1], 99); 

    printf("[DEBUG] buffer @ %p: '%s'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: '%s'\n", datafile, datafile);

    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd == -1)
        fatal("in main() while opening file");

    printf("[DEBUG] file descriptor is %d\n", fd);

    userid = getuid();

    if(write(fd, &userid, 4) == -1)
        fatal("in main() while writing userid to file");

    write(fd, "\n", 1);

    if(write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main() while writing buffer to file");

    write(fd, "\n", 1);

    if(close(fd) == -1)
        fatal("in main() while closing file");

    printf("Note has been saved.\n");

    free(buffer);
    free(datafile);

    return 0; 
}


// Notesearch

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"
#define FILENAME "/var/notes"

int print_notes(int, int, char *); // Function to print notes.
int find_user_note(int, int); // Function to find a note by user ID.
int search_note(char *, char *); // Function to search for a keyword in a note.
void fatal(char *); // Fatal error handler.

int main(int argc, char *argv[]) {
    int userid, printing = 1, fd;
    char searchstring[100];

    if(argc > 1)
        strncpy(searchstring, argv[1], 99); // Use strncpy for safety.
    else
        searchstring[0] = 0; // Set searchstring to an empty string if no argument is provided.

    userid = getuid();

    fd = open(FILENAME, O_RDONLY); // Open the file in read-only mode.
    if(fd == -1)
        fatal("in main() while opening file for reading");

    while(printing)
        printing = print_notes(fd, userid, searchstring); // Continue printing notes until done.

    printf("-------[ end of note data ]-------\n");
    close(fd); // Close the file.

    return 0;
}

// Function to print notes for a given user ID that match an optional search string.
// Returns 0 at the end of the file, 1 if there are more notes.
int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte = 0, note_buffer[100];

    note_length = find_user_note(fd, uid); // Find the note for the given user ID.
    if(note_length == -1)
        return 0; // Return 0 if end of file is reached.

    read(fd, note_buffer, note_length); // Read the note data.
    note_buffer[note_length] = 0; // Null-terminate the string.

    if(search_note(note_buffer, searchstring)) // If the search string is found,
        printf("%s", note_buffer); // Print the note using %s to avoid format string issues.

    return 1; // Continue searching for more notes.
}

// Function to find the next note for a given user ID.
// Returns -1 if the end of the file is reached, otherwise returns the length of the found note.
int find_user_note(int fd, int user_uid) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while(note_uid != user_uid) { // Loop until a note for user_uid is found.
        if(read(fd, &note_uid, 4) != 4) // Read the user ID.
            return -1; // Return -1 if end of file is reached.

        if(read(fd, &byte, 1) != 1) // Read the newline separator.
            return -1;

        byte = length = 0;
        while(byte != '\n') { // Calculate the length of the note.
            if(read(fd, &byte, 1) != 1)
                return -1;
            length++;
        }
    }

    lseek(fd, length * -1, SEEK_CUR); // Move the file pointer back to the start of the note.
    printf("[DEBUG] found a %d byte note for user id %d\n", length, note_uid);
    return length; // Return the length of the note.
}

// Function to search a note for a given keyword.
// Returns 1 if a match is found, 0 if there is no match.
int search_note(char *note, char *keyword) {
    int i, keyword_length, match = 0;

    keyword_length = strlen(keyword);
    if(keyword_length == 0) // If there is no search string,
        return 1; // Always return a match.

    for(i = 0; i < strlen(note); i++) { // Iterate over each character in the note.
        if(note[i] == keyword[match]) // If the current character matches the keyword,
            match++; // Move to the next character in the keyword.
        else {
            if(note[i] == keyword[0]) // If it matches the first character of the keyword,
                match = 1; // Start matching from the first character.
            else
                match = 0; // Reset match if no characters match.
        }

        if(match == keyword_length) // If the entire keyword is matched,
            return 1; // Return a successful match.
    }
    return 0; // Return no match if the keyword is not found.
}
