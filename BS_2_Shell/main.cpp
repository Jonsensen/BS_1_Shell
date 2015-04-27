#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/stat.h>				// open()
#include <signal.h>				// signal()
#include <fcntl.h>				// open()
#include <stdio.h>				// printf(), ...
#include <time.h>				// time(), ...
#include <string.h>				// strtok()
#include <iostream>
#include <sstream>
#include <vector>
#define MAXLINE 100
#define MOD "exit with CTR C"




int read_command(char *command, char *parameters[]) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
    
    char wholeLine[MAXLINE];
    
    std::cin.getline(wholeLine,MAXLINE);
  
    std::vector<char*>args;
    
    //char* prog= strtok(command, " ");
    command=strtok(wholeLine," "); // Hier anders !!!
    char* tmp= command;
    while(tmp!=NULL){
        args.push_back(tmp);
        tmp=strtok(NULL, " ");
    }
    // argv = parameters
    
    parameters=new char*[args.size()+1];
    for (int i=0; i<args.size(); i++) {
        parameters[i]=args[i];
       }
    
     parameters[args.size()]=NULL;
   
  
    /*
    std::string tmpStr=command;
    std::stringstream tmpStream(tmpStr);
 */
    
    
    
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
        std::cout<<parameters<<std::endl;
        std::cout<<command<<std::endl;
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        }
        
        else if (childPid == 0) { // child process
            std::cout<<"Im Kind"<<std::endl;
            std::cout<<*parameters<<std::endl;
            std::cout<<command<<std::endl;
            
           //status= execvp(parameters[0], parameters); // executes command
            status=execvp(command,parameters);
        
            exit(3);
        }
        
        else { // father
            waitpid(childPid, &status, WUNTRACED | WCONTINUED);
        }
    }
    
  //  close(fd);
    //exit(0);
    return 0;
}
