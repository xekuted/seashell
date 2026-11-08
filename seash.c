#include <stdio.h>
#include <string.h>

//The shell is essentially a process that runs as a loop. It follows REPL which stands for Read, Eval, Print and Loop.

//I'll try to build a minimal implementation of REPL here where I'll just take in input from the user and print it. The program will only end when the user sends a specific command or EOF.

int main(){
while (1){// This will be the loop protion of our shell that will keep our program running.
    char cmd[1024]; //Setting the input size

    printf("> ");// The prompt that appears on every shell like $ / >

    fflush(stdout); // Forces buffered output to be displayed immediately, ensuring the prompt appears before waiting for user input.

    if(fgets(cmd, sizeof(cmd), stdin)==NULL)// Taking input from the user, if the return value is NULL then we'll end the loop)
    {
        break;
    }

cmd[strcspn(cmd, "\n")] = '\0'; //Removing newline

if(cmd[0]=='\0'){ //If the input is empty, continue with input taking
    continue;
    }

    printf("%s \n",cmd);//Printing the input
}

}
