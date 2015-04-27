
//#include <sys/types.h>  // type definitions, e.g., pid_t
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/stat.h>				// open()
#include <signal.h>				// signal()
#include <fcntl.h>				// open()
#include <stdio.h>				// printf(), ...
#include <time.h>				// time(), ...
#include <string.h>				// strtok()
#include <vector>
#include <iostream>
#define MAXLINE 100
#define MOD "exit with CTR C" // Noch nicht Implementiert...


int read_command(char *command, char *parameters[]) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
   // Hier Auslagern
    return 0;
} // read_command



int main(int argc, char *argv[])
{
    
    int childPid;
    int status;
    char command[MAXLINE];
   // char *parameters[MAXLINE];
    int noParams;
    
    while ( true )
    {
        // Ausgabe aktueller Pfad hier einfügen..
        std::cout<<"$";
        std::cin.getline( command, MAXLINE );
        
        std::vector<char*> args;
        char* prog = strtok( command, " " );
        char* tmp = prog;
        while ( tmp != NULL )
        {
            args.push_back( tmp );
            tmp = strtok( NULL, " " );
        }
        
                char** parameters = new char*[args.size()+1];
        
            for ( int k = 0; k < args.size(); k++ )
            parameters[k] = args[k];
        
        parameters[args.size()] = NULL; // Nullterminieren
        
        
        /* Implementation von cd Befehelen
            if (!strcmp (prog, "cd"))
            {
                if (argv[1] == NULL)
                {
                    chdir ("/");
                }
                else
                {
                    chdir (argv[1]);
                }
                perror (command);
            */
        
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        }
        
        
        else if (childPid == 0) { // child process
            //std::cout<<"Im Kind !"<<std::endl;
            execvp(prog, parameters); // executes command
            exit(3);
        }

        else { // Vater
            //std::cout<<"Im Vater"<<std::endl;
        waitpid(childPid, &status, WUNTRACED | WCONTINUED); // Warten auf Kind
        }
        
        
    }
    
    return 0;
}