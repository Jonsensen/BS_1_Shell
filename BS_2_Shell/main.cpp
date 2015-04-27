
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
#define MOD "exit with CTR C"
using namespace std;

int read_command(char *command, char *parameters[]) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
   // ...
    return 0;
} // read_command



int main(int argc, char *argv[])
{
    
    int childPid;
    int status;
    char command[MAXLINE];
    char *parameters[MAXLINE];
    int noParams;
    
    
    while ( true )
    {
        // Show prompt.
        //      cout << get_current_dir_name () << "$ " ;
        
        cout<<"$";
        char command[MAXLINE];
        cin.getline( command, MAXLINE );
        
        vector<char*> args;
        char* prog = strtok( command, " " );
        char* tmp = prog;
        while ( tmp != NULL )
        {
            args.push_back( tmp );
            tmp = strtok( NULL, " " );
        }
        
        char** argv = new char*[args.size()+1];
        for ( int k = 0; k < args.size(); k++ )
            argv[k] = args[k];
        
        argv[args.size()] = NULL;
        
        if ( strcmp( command, "exit" ) == 0 ) //  Hier abbruch mit exit
        {
            return 0;
        }
        else
        {
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
            }
            else
            {
                pid_t kidpid = fork();
                
                if (kidpid < 0)
                {
                    perror( "Internal error: cannot fork." );
                    return -1;
                }
                else if (kidpid == 0)
                {
                    // I am the child.
                   status=execvp (prog, argv);
                    
                    // The following lines should not happen (normally).
                    perror( command );
                    return -1;
                }
                else
                {
                    waitpid(kidpid, &status, WUNTRACED | WCONTINUED);
                    // I am the parent.  Wait for the child.
                  /*
                    if ( waitpid( kidpid, 0, 0 ) < 0 )
                    {
                        perror( "Internal error: cannot wait for child." );
                        return -1;
                    }
                   */
                }
            }
        }
    }
    
    return 0;
}