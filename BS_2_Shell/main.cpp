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
#include <string>
#include <sstream>
#include <vector>
#define MAXLINE 100
#define MOD "exit with CTR C"

// Hier neue Version
int read_command(std::string &command, std::vector<std::string> &parameters) { // prompt for user input and read a command line
    
    //fprintf(stdout, "$ ");
    std::cout<<"$";
 
    std::string wholeLine;
    std::string tmpString;
    std::getline(std::cin, wholeLine);
    std::stringstream ss(wholeLine);
    
    ss>>command;

    while (ss.good()) {
        ss>>tmpString;
        parameters.push_back(tmpString.c_str());
        }
    
    return(0); // still not working
} // read_command

int main(int argc, char *argv[]) {
    int childPid;
    int status;
    std::string command;
    std::vector<std::string> parameters;
    int noParams;
    std::vector<const char *> params;
    
    while (1) {
        noParams = read_command(command, parameters); // read user input
        
        // Kopiere Parameter in const *char vector
        for (int i=0; i<parameters.size(); i++) {
            params.push_back(parameters[i].c_str());
         }
        
 /* Testoutput
        for (int i=0; i<params.size(); i++) {
            std::cout<<"params an stelle "<<i<<params[i]<<std::endl;
        }
        std::cout<<"Comm:"<<comm<<std::endl;
   */
        
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        } else if (childPid == 0) { // child process
            std::cout<<"Im Kindprozess !"<<std::endl;
            std::cout<<"10 sek warten"<<std::endl;
            sleep(10); // 10 sek sleep for test
           status= execvp(const_cast<char*>(command.c_str()),const_cast<char**>(params.data())); // executes command
            
            exit(3);
        } else { // father
                 std::cout<<"Vater wartet auf Kind..."<<std::endl;
            waitpid(childPid, &status, WUNTRACED | WCONTINUED);
            std::cout<<"Kind fertig "<<std::endl;
            std::cout<<"status: "<<status<<std::endl;
      }
        
        exit(0);
    }
    
    return (0);
    //    close(fd); // ??
   // exit(0);
}


