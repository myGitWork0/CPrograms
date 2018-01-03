#include <string.h>
#include <unistd.h>
#include <sys/types.h>  
#include <errno.h>     
#include <stdio.h>      
#include <sys/wait.h>
#include <stdlib.h>     
#include <signal.h>
#define MAX_LINE_SIZE 255					//user defined macro
extern int errno ;
void sigintHandler(int sig_num);				//function declaration
int main(){
	signal(SIGINT, sigintHandler);				//calling the signal system call
	while(1){						//infinite loop to print myshell and take input
		int i=0,j=0,k=0,status;
		char line[MAX_LINE_SIZE];
		char *words[20];
		char e[4]="exit";	
		char r[3]="run";
		printf("myshell> ");			
		fgets(line, MAX_LINE_SIZE, stdin);		//taking input from input stream
		if(!strcmp(line,"\n")){
			continue;				//if enter key is pressed
		}
		char *str=strtok(line," ");			//first word will be taken using stringtokenizer
		if(!strncmp(str,e,4)){			
			break;					//checks first word with exit	
		}
		if(!strncmp(str,r,3))				//checks with run
		{						
			words[i] = strtok(NULL,";\n");		//tokenizing with \n and ;
			while (words[i]!=NULL)			//tokenizing till the end of line
			{	
				i++;				
				words[i] = strtok(NULL,";\n");	//store individual commands in array
			}
			for(j=0;j<i;j++)			
			{
				char *words1[5];
				k=0;		
				words1[k] = strtok(words[j]," \n");	//tokenizing using the space to get the options
				while (words1[k]!=NULL)			//tokenizing using the space to get the options
				{	
					k++;				
					words1[k] = strtok(NULL," \n");	//storing in word1 array
				}
				pid_t result=fork();			//splitting the process
				if(result<0){				//if forking did not happen 
					printf("Error is:%s\n",strerror(errno));
				 }
				if(result>0){
					wait(&status);			//parent process will be kept in waiting
				}		
				if(result==0){						
					printf("myshell: started child pid %d\n",getpid());	//prints the process id of running child process
					if(execvp(*words1,words1)==-1){				//checks if the command is executing or not
						printf("myshell: No such file or directory %s\n",*words1);
					}
				}	 
			}
		}
	else {
		printf("myshell: %s is not a valid command\n",strtok(str,"\n"));//tokenizes and prints the first word
		continue;							//iterates the loop
	}
	}
	exit(EXIT_SUCCESS);
}
void sigintHandler(int sig_num)
{
        signal(SIGINT, sigintHandler);						//catches signal
}