#include <string.h>
// Defining the parser function
void parser(char cmd[], char *argv[]){
    char *ptr = strtok(cmd, " "); // strtok() starts tokenizing cmd using space as the delimiter.
    // It returns a pointer to the beginning of the first token.
    // strtok() modifies the original cmd array by replacing delimiters (spaces) with null terminators ('\0'). It does NOT create new strings or allocate memory.
    int count = 0; // count keeps track of the current position in argv.
    while(ptr != NULL){// Continue extracting tokens until strtok() returns NULL.

        argv[count] = ptr; // Store the pointer returned by strtok() in argv. argv[count] simply stores the address of the token inside the original cmd array.

        ptr = strtok(NULL, " "); // Passing NULL tells strtok() to resume from where the previous call stopped.
        count += 1;
    }

    argv[count] = NULL; // execvp() expects argv to end with NULL.This tells it where the argument list finishes.

    for(int i=0;i<count;i++){
        if(strcmp(argv[i], ";") == 0){
            argv[i]=NULL;
        }

    }
}
