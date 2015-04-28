#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/stat.h>				// open()
#include <sys/types.h>
#include <signal.h>				// signal()
#include <fcntl.h>				// open()
#include <stdio.h>				// printf(), ...
#include <time.h>				// time(), ...
#include <string.h>				// strtok()
#include <vector>
#include <iostream>
#include <fstream>
#define MAXLINE 100
#define MOD "exit with CTR C"

bool isinBackground;

// Zum Beenden mit CTR C
void handler(int s) {
    char choice;
    std::cout<<"Programm wirklich beenden ? j/n "<<std::endl;
    std::cin>>choice;
    if (choice=='j'|choice=='J'){
        exit(0);
    }
    
    return;
}

//Ausgabe des Aktuellen verzeichnisses Funktioniert nicht


// Funktioniert noch nicht ?!
void writeLog(char command[]){

    std::ofstream logFile;
    logFile.open("log.txt",std::ios::out);

    if (logFile.is_open()){
    logFile.open ("log.txt");
    //logFile << command;
    logFile <<"Test"; // Funktioniert nicht. Warum ?
    logFile.close();
    }
    else
        std::cout<<"Problem beim oeffnen von log.txt"<<std::endl;
    
}


void printDisplayStatus(int status){

    
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

    
}

int read_command(char* (&command),char** (&parameters)) { // prompt for user input and read a command line
    fprintf(stdout, "$ ");
   // Hier Auslagern
    
    
    
    return 0;
} // read_command


int main(int argc, char *argv[])
{
    //chdir(../home/schuette/tmp);
    signal(SIGINT, handler);
    int childPid;
    int status;
    //char command[MAXLINE];
    
   // char *parameters[MAXLINE];
    int noParams; // wird gebraucht, wenn read_command ausgeladgert ist
    
    char* command=NULL;
    char** parameters=NULL;
    
    
    while (true)
    {
        isinBackground=false;
        
        // Von hier auslagern
        char wholeLine[MAXLINE];
        // Ausgabe aktueller Pfad hier einfügen..
        std::cout<<"$";
        std::cin.getline( wholeLine, MAXLINE );
        
        
      
      /*
        // Prüfen ob & in Befehl -> Prozess in Hintergrund
        std::string und = "&";
        std::string testString = wholeLine;
        std:: size_t found = testString.find(und);
        if (found!=std::string::npos){
            std::cout <<"Es wurde ein und Zeichen gefunden!"<<std::endl;
            isinBackground=true;
    
        }
       */
        
        writeLog(wholeLine);
        // String zerlegen und in args schreiben:
        std::vector<char*> args;
        //char* command = strtok( wholeLine, " " );
        command= strtok( wholeLine, " ");
        char* tmp = command;
        while ( tmp != NULL )
        {
            args.push_back( tmp );
            tmp = strtok( NULL, " " );
        }
        
        
    
        
        // vector args in parameters kopieren
        parameters=new char*[args.size()+1];
        
        for ( int i = 0; i < args.size(); i++ )
            parameters[i] = args[i];
        
        parameters[args.size()] = NULL; // Nullterminieren
        
        
        
        
        //  Implementation von cd Befehelen -> Weil cd kein ausführbarer Befehl ist
        // Bei wechseln in verzeichnis Fehleranzeige, weil in execvp ausgeführt -> fixen
        if (!strcmp (command, "cd"))
        {
            if (parameters[1] == NULL)
            {
                chdir ("/");
            }
            else
            {
                chdir (parameters[1]);
                delete parameters;
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
            if(!isinBackground){
            waitpid(childPid, &status, WUNTRACED | WCONTINUED); // Warten auf Kind
            }
          /*  else
            {
                waitpid(childPid, &status, WNOHANG);
                std::cout<<"im Hintergrund hier steht Prozess ID "<<std::endl;
            }
            */
        }
        
        //printDisplayStatus(status);
        
        
    }// Ende while(true)
    
    return 0;
}