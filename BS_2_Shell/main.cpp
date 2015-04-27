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

int read_command(char* (&command),char** (&parameters)) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
   // Hier Auslagern
    

   
    
    return 0;
} // read_command


int main(int argc, char *argv[])
{
    
    int childPid;
    int status;
    //char command[MAXLINE];
    
   // char *parameters[MAXLINE];
    int noParams; // wird gebraucht, wenn read_command ausgeladgert ist
    
    char* command=nullptr;
    char** parameters=nullptr;
    
    
    while (true)
    {
        
        
        
        // Von hier auslagern
        char wholeLine[MAXLINE];
        // Ausgabe aktueller Pfad hier einfügen..
        std::cout<<"$";
        std::cin.getline( wholeLine, MAXLINE );
        // String zerlegen und in args schreiben:
        std::vector<char*> args;
        //char* command = strtok( wholeLine, " " );
        command= strtok( wholeLine, " " );
        char* tmp = command;
        while ( tmp != NULL )
        {
            args.push_back( tmp );
            tmp = strtok( NULL, " " );
        }
        
        // vector args in parameters kopieren
        // char** parameters = new char*[args.size()+1];
        parameters=new char*[args.size()+1];
        
        for ( int i = 0; i < args.size(); i++ )
            parameters[i] = args[i];
        
        parameters[args.size()] = NULL; // Nullterminieren
        
        
        
        //  Implementation von cd Befehelen -> Weil cd kein ausführbarer Befehl ist
        if (!strcmp (command, "cd"))
        {
            if (parameters[1] == NULL)
            {
                chdir ("/");
            }
            else
            {
                chdir (parameters[1]);
            }
        }
        
        // Bis hier auslagern!

        
        
        //noParams=read_command(command, parameters);
        
        if ((childPid = fork()) == -1) { // create process
            fprintf(stderr, "can't fork!\n");
            exit(3);
        }
        
        
        else if (childPid == 0) { // child process
            //std::cout<<"Im Kind !"<<std::endl;
            execvp(command, parameters); // executes command
            exit(3);
        }

        else { // Vater
            //std::cout<<"Im Vater"<<std::endl;
            waitpid(childPid, &status, WUNTRACED | WCONTINUED); // Warten auf Kind
        }
        
        
    }// Ende while(true)
    
    return 0;
}