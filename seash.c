
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "looks.h"
#include <unistd.h>// for fork()
#include <sys/types.h> //for PID
#include <sys/wait.h> //for using waitpid
#include <stdlib.h>// for the built in commands

    //Global Vars
    char cmd[1024]; //Setting the input size
    char *argv[1024]; //The array that will hold individual tokens
    char cwd[1000]; //current working dir

    //The shell is essentially a process that runs as a loop. It follows REPL which stands for Read, Eval, Print and Loop.


    // Phase - 1 (REPL implementation)

    int main(){

    print_banner(); // Displaying the SeaShell startup banner

    while (1){// This will be the loop protion of our shell that will keep our program running.

        display_prompt(); // Displaying the shell prompt

        fflush(stdout); // Forces buffered output to be displayed immediately, ensuring the prompt appears before waiting for user input.

        if(fgets(cmd, sizeof(cmd), stdin)==NULL)// Taking input from the user, if the return value is NULL (cause of EOF) then we'll end the loop
        {
            break;
        }

    cmd[strcspn(cmd, "\n")] = '\0'; //Removing newline

    if(cmd[0]=='\0'){ //If the input is empty, continue with input taking
        continue;
        }

    parser(cmd, argv); //Tokenising the input cmd

    // Phase - 3: Built ins
    // Implemented before phase-2 cause things won't work as expected othwerwise
    // Checking if the command is just blank spaces

    if(argv[0]==NULL){
        continue;
    }else{
        //cd command (Built-in #1)
        if(strcmp(argv[0], "cd")==0){
            if(argv[1]==NULL){//If nothing is entered after cd
                if(getenv("HOME")==NULL){//checking whether HOME path exists or not
                    fprintf(stderr, ORANGE "cd: HOME not set\n" RESET);
                    continue;
                }else{
                    if(chdir(getenv("HOME"))==-1){//Going to the home directory and checking whether it fails to change or not
                        fprintf(stderr, ORANGE);
                        fprintf(stderr, ORANGE);
                perror("cd");
                fprintf(stderr, RESET);
                        fprintf(stderr, RESET);//printing an error if changing to HOME fails
                        continue;
                    }
            }
        }else{
            if(chdir(argv[1])==-1){// if chdir fails
                fprintf(stderr, ORANGE);
                perror("cd");
                fprintf(stderr, RESET);
                continue;
            }
        }   //exit command
        }else if (strcmp(argv[0], "exit") == 0) {
            return 0;
        }//pwd command
        else if (strcmp(argv[0], "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                    fprintf(stderr, ORANGE);
                    perror("pwd");
                    fprintf(stderr, RESET);
                }
            }//help command
        else if (strcmp(argv[0], "help") == 0) {
            printf("\n" GREEN " Built-in commands:" RESET "\n\n");
            printf(" " ORANGE "cd" RESET "              Change working directory\n");
            printf(" " ORANGE "pwd" RESET "             Print working directory\n");
            printf(" " ORANGE "exit" RESET "            Exit the shell\n");
            printf(" " ORANGE "help" RESET "            Display this help message\n");
            }
        else{
            //Phase - 2 : Parsing

            pid_t PID =fork(); //storing the value of fork's return value

            if(PID>0){
                //parent

               waitpid(PID,NULL,0); //waiting for the child process to end so that it doesn't print another prompt while the child process is still running.
            }
            else if(PID<0){
                //error
                fprintf(stderr, ORANGE);
                perror("fork");
                fprintf(stderr, RESET); //printing the error if fork fails.
            }else{
                //child
                execvp(argv[0], argv); // Replaces the child process with the requested program.
                fprintf(stderr, ORANGE);
                perror("execvp");
                fprintf(stderr, RESET);//printing an error if execvp fails.
                _exit(127);//exiting the process if it fails
            }

        }


}



    }
    }
