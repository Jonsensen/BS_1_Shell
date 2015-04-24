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

void ctrcHandler(int sig)
{
    std::cout <<"CTR C wurde gedrückt !"<<std::endl;
    return;
}

int read_command(std::string &command, std::vector<std::string> &parameters) { // prompt for user input and read a command line
    
    //fprintf(stdout, "$ ");
    std::cout<<"$";
 
    std::string wholeLine;
    std::string tmpString;
    std::getline(std::cin, wholeLine);
    std::stringstream ss(wholeLine);
    
    ss>>command;
    
    parameters.clear(); // ?!
    
    parameters.push_back(command);
    
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
    
   signal(SIGINT, ctrcHandler); // Funktioniert noch nicht..
    
    while (1) {
        noParams = read_command(command, parameters); // read user input
        if(noParams!=0){
            return (0);
        }
        
        
    /*    //   /*Testoutput
        for (int i=0; i<parameters.size(); i++) {
            std::cout<<"parameters an stelle "<<i<<parameters[i]<<std::endl;
        }
      */
        
      /*  if(params.size()>0){
            for (int x=0; x<params.size();x++)
            {
        params.pop_back();
            }
        }
       */
        params.clear();
     
        
        // Kopiere Parameter in const *char vector
        for (int i=0; i<parameters.size(); i++) {
            params.push_back(parameters[i].c_str());
            
         }
        
        
        
        /*Testoutput
        for (int i=0; i<params.size(); i++) {
            std::cout<<"params an stelle "<<i<<params[i]<<std::endl;
        }
        std::cout<<"Command: "<<command<<std::endl;
         */
        
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        } else if (childPid == 0) { // child process
          //  std::cout<<"Im Kindprozess !"<<std::endl;
          //  std::cout<<"1 sek warten"<<std::endl;
          //  sleep(1); // 1 sek sleep for test
            
         /* // Child Testoutput
            for (int i=0; i<params.size(); i++) {
                std::cout<<"params in Kind an stelle "<<i<<params[i]<<std::endl;
            }
            std::cout<<"Command in Kind : "<<command<<std::endl;
          
            //char ** test12 =const_cast<char**>(params.data());
            
            //std::cout<<"test12 ohne const: "<<*test12<<std::endl;
           */
          
           status= execvp(const_cast<char*>(command.c_str()),const_cast<char**>(params.data())); // executes command // Buggy
            params.clear();
            parameters.clear();
            
            exit(3);
        } else { // father
            //     std::cout<<"Vater wartet auf Kind..."<<std::endl;
            waitpid(childPid, &status, WUNTRACED | WCONTINUED);
            //std::cout<<"Kind fertig- wieder im Vater "<<std::endl;
        }
        
        
        // Display Status
        if (WIFEXITED(status)){
            std::cout <<"Kind wurde normal beendet. Status : "<<WEXITSTATUS(status)<<std::endl;
        }
        
        else if (WIFSIGNALED(status)){
            std::cout<<"Kind wurde nicht norrmal beendet. Status : "<<WTERMSIG(status)<<std::endl;
        }
        
        else if (WIFSTOPPED(status)){
            std::cout<<"Kind wurde gerade gestoppt. Status : "<<WEXITSTATUS(status)<<" Signalnr: "<<WSTOPSIG(status)<<std::endl;
        }
        
        
        
        
       // exit(0);
        
    }// end while(1)
    
    return (0);
    //    close(fd); // ??
   // exit(0);
}


