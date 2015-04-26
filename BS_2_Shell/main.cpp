#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/stat.h>				// open()
#include <signal.h>				// signal()
#include <fcntl.h>				// open()
#include <stdio.h>				// printf(), ...
#include <time.h>				// time(), ...
#include <string.h>				// strtok()
#define MAXLINE 100
#define MOD "exit with CTR C"


int read_command(char *command, char *parameters[]) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
        
    
    
    return 0;
} // read_command

int main(int argc, char *argv[]) {
    int childPid;
    int status;
    char command[MAXLINE];
    char *parameters[MAXLINE];
    int noParams;
    
    while (1) {
        noParams = read_command(command, parameters); // read user input
        return 0;
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        } else if (childPid == 0) { // child process
            //execvp(command, parameters); // executes command
            exit(3);
        } else { // father
            waitpid(childPid, &status, WUNTRACED | WCONTINUED);
        }
    }
    
  //  close(fd);
    //exit(0);
    return 0;
}
