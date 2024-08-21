#include <stdio.h>
#include <string.h>

int cml(int arg_count, char *arg_list[]) {
    int i;
    printf("There were %d arguments provided:\n", arg_count);
    for(i=0; i < arg_count; i++)
    printf("argument #%d\t-\t%s\n", i, arg_list[i]);
}

void usage(char *program_name) {
    printf("Usage: %s <message> <# of times to repeat>\n", program_name);
    exit(1);
}

int convert(int argc, char *argv[]) {
    int i, count;
    if(argc < 3) // If fewer than 3 arguments are used,
    usage(argv[0]); // display usage message and exit.
    count = atoi(argv[2]); // Convert the 2nd arg into an integer.
    printf("Repeating %d times..\n", count);
    for(i=0; i < count; i++)
    printf("%3d - %s\n", i, argv[1]); // Print the 1st arg.
}

int convert_2(int argc, char *argv[]) {
    int i, count;
    // if(argc < 3) // If fewer than 3 arguments are used,
    // usage(argv[0]); // display usage message and exit.
    count = atoi(argv[2]); // Convert the 2nd arg into an integer.
    printf("Repeating %d times..\n", count);
    for(i=0; i < count; i++)
    printf("%3d - %s\n", i, argv[1]); // Print the 1st arg.
}




