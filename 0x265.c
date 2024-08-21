#include <stdio.h>
#include <string.h>

int typecasting() {
    int a, b;
    float c, d;
    a = 13;
    b = 5;
    c = a / b; // Divide using integers.
    d = (float) a / (float) b; // Divide integers typecast as floats.
    printf("[integers]\t a = %d\t b = %d\n", a, b);
    printf("[floats]\t c = %f\t d = %f\n", c, d);
}

int pointer_types() {
    int i;
    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};
    char *char_pointer;
    int *int_pointer;
    char_pointer = char_array;
    int_pointer = int_array;

    for (i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[integer pointer] points to %p, which contains the integer %d\n",
        int_pointer, *int_pointer);
        int_pointer = int_pointer + 1;
    }

    for(i=0; i < 5; i++) { // Iterate through the char array with the char_pointer.
        printf("[char pointer] points to %p, which contains the char '%c'\n",
        char_pointer, *char_pointer);
        char_pointer = char_pointer + 1;
    }
}

int pointer_types_2() {

    int i;
    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};
    char *char_pointer;
    int *int_pointer;
    char_pointer = int_array; // The char_pointer and int_pointer now
    int_pointer = char_array; // point to incompatible data types.

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[integer pointer] points to %p, which contains the char '%c'\n",
        int_pointer, *int_pointer);
        int_pointer = int_pointer + 1;
    }

    for(i=0; i < 5; i++) { // Iterate through the char array with the char_pointer.
        printf("[char pointer] points to %p, which contains the integer %d\n",
        char_pointer, *char_pointer);
        char_pointer = char_pointer + 1;
    }

}

int pointer_types_3() {
    int i;
    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};
    char *char_pointer;
    int *int_pointer;
    char_pointer = (char *) int_array; // Typecast into the
    int_pointer = (int *) char_array; // pointer's data type.

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[integer pointer] points to %p, which contains the char '%c'\n",
        int_pointer, *int_pointer);
        int_pointer = (int *) ((char *) int_pointer + 1);
    }

    for(i=0; i < 5; i++) { // Iterate through the char array with the char_pointer.
        printf("[char pointer] points to %p, which contains the integer %d\n",
        char_pointer, *char_pointer);
        char_pointer = (char *) ((int *) char_pointer + 1);
    }
}

int pointer_types_4() {
    int i;
    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};
    void *void_pointer;
    void_pointer = (void *) char_array;

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[char pointer] points to %p, which contains the char '%c'\n",
        void_pointer, *((char *) void_pointer));
        void_pointer = (void *) ((char *) void_pointer + 1);
    }

    void_pointer = (void *) int_array;

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[integer pointer] points to %p, which contains the integer %d\n",
        void_pointer, *((int *) void_pointer));
        void_pointer = (void *) ((int *) void_pointer + 1);
    }
}

int pointer_types_5() {
    int i;
    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5] = {1, 2, 3, 4, 5};
    unsigned int hacky_nonpointer;
    hacky_nonpointer = (unsigned int) char_array;

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[hacky_nonpointer] points to %p, which contains the char '%c'\n",
        hacky_nonpointer, *((char *) hacky_nonpointer));
        hacky_nonpointer = hacky_nonpointer + sizeof(char);
    }

    hacky_nonpointer = (unsigned int) int_array;

    for(i=0; i < 5; i++) { // Iterate through the int array with the int_pointer.
        printf("[hacky_nonpointer] points to %p, which contains the integer %d\n",
        hacky_nonpointer, *((int *) hacky_nonpointer));
        hacky_nonpointer = hacky_nonpointer + sizeof(int);
    }
}

