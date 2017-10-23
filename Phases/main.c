// Raul Martinez

#include <stdio.h>
#include <string.h>
#include "phase2.h"

void breakup(char * in, char * p1, char * p2, char * p3)
{
    int i = 0;
    int j = 0;
    
    while (in[i] != ' ' && i < strlen(in) - 1)
    {
        p1[j] = in[i];
        i++;
        j++;
    }
    
    j = 0;
    i++;
    
    while (in[i] != ' ' && i < strlen(in) - 1)
    {
        p2[j] = in[i];
        i++;
        j++;
    }
    
    j = 0;
    i++;
    
    while (in[i] != ' ' && i < strlen(in) - 1)
    {
        p3[j] = in[i];
        i++;
        j++;
    }
    
}

char * inFile;

int main()
{
    char input[100] = "";
    char part1[10] = "";
    char part2[10] = "";
    char part3[10] = "";
    
    
    printf("%s\n\n", "Welcome to the coding platform. Type \"help\" for assistance.");
    
    do
    {
        printf("%s", ":: ");
        
        fgets(input, 60, stdin);
        breakup(input, part1, part2, part3);
        
        
        
        if (strcmp(part1, "help") == 0)
        {
            printf("-------------------------- \n HELP COMMANDS: \n load <filename> : call the load function to load the specified file. \n execute : execute the program that was previously loaded in memory. \n debug : execute in debug mode. \n dump start end : call the dump function, passing the values of start and end.  Start and end will be hexadecimal values. \n help : display list of available commands. \n assemble <filename> : assemble an SIC assembly language program into a load module and store it in a file. \n directory : list the files stored in the current directory. \n exit : exits program. \n -------------------------- \n ");
        }
        
        else if (strcmp(part1, "directory") == 0)
        {
            system("ls");
        }
        
        else if(strcmp(part1, "load") == 0)
        {
            if(strcmp(part2,"\0") == 0)
            {
                printf("LOAD takes in 1 parameter.\n");
            }
            
            else
            {
                if( access( part2, F_OK ) != -1 )
                {
                    inFile = part2;
                    printf("'%s' has been loaded.\n", inFile);
                }
                else
                {
                    printf("File does not exist.\n");
                }
            }
        }
        
        else if(strcmp(part1, "assemble") == 0)
        {
            if(strcmp(part2,"\0") == 0)
            {
                printf("ASSEMBLE takes in 1 parameter.\n");
            }
            
            else
            {
                if( access( part2, F_OK ) != -1 )
                {
                    assemble(part2);
                }
                else
                {
                    printf("File does not exist.\n");
                }
            }
        }
        
        else if (strcmp(part1, "execute") == 0)
        {
            printf("Under Construction.\n");
        }
        
        else if (strcmp(part1, "debug") == 0)
        {
            printf("Under Construction.\n");
        }
        
        else if (strcmp(part1, "dump") == 0)
        {
            if(strcmp(part2, "start") == 0)
            {
                if (strcmp(part3, "end") == 0)
                    printf("Under Construction.\n");
                else
                    printf("Takes 2 parameters.\n");
            }
            else
                printf("Takes 2 parameters.\n");
        }
        
        else if (strcmp("exit", part1) != 0)
        {
            printf("Invalid command.\n");
        }
        
        
        if (strcmp(part1, "exit") != 0)
        {
            memset(input, 0, 10);
            memset(part1, 0, 10);
            memset(part2, 0, 10);
            memset(part3, 0, 10);
        }
        
    }
    
    while (strcmp(part1, "exit") != 0);
    printf("%s\n", "Exited...");
    
}



