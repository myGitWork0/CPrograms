#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>									//header files
void display_message(int sig)						//subfunction definition
{
	printf("duplicatefile: still copying...\n");	
	alarm(1);										//resetting the alarm.
}
int main(int argc,char *argv[]){
	int fid_in, fid_out;							
	int num_bytes = 0;
	ssize_t n, n_w;									//variable declaration
	char *buffer = malloc(sizeof(char) * 100);		//variable declared dynamically
	signal(SIGALRM, display_message);				//signal call
	if(argc>3){										//checks for correct number of inputs
		printf("Too many arguments !!\n");		
		printf("Usage : duplicatefile inputfile outputfile\n");
		exit(EXIT_FAILURE);							//predefined macro used to indicate abnormal exit.
	}
	if(argc<3){										//checks for correct number of inputs
		printf("Too few arguments !!\n");
		printf("Usage : duplicatefile inputfile outputfile\n");
		exit(EXIT_FAILURE);							//predefined macro used to indicate abnormal exit.
	}
	fid_in = open(argv[1],O_RDONLY,0);				//opening file in read mode
	if(fid_in<0){
		printf("Couldn't open file %s: %s\n",argv[1],strerror(errno));	//prints the appropriate error 
		exit(EXIT_FAILURE);
	}
	fid_out = open(argv[2], O_WRONLY | O_CREAT,00600);	//opening file in write mode and creating file if doesnt exists with owner permissions to read and write.
	if(fid_out<0){									//fid_out will have negative value if it doesnt open correctly
		printf("Couldn't open file %s: %s\n",argv[2],strerror(errno));
		exit(EXIT_FAILURE);							
	}
	alarm(1);										//setting an alarm for about 1 second
	while((n=read(fid_in,(void *)buffer,100))>0){	//reading file till end of file
		n_w=write(fid_out,(void *)buffer,n);		//writing the content of buffer into file 
		if(n_w<0){									//problem reading the file
			printf("Problem writing to file :%s\n",strerror(errno));
			exit(EXIT_FAILURE);
		}
		num_bytes += n;								//sums the total number of bytes written into file
	}
	free(buffer);									//freeing up the buffer.
	if(n<0){
		printf("Problem writing to file :%s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(fid_in);
   	close(fid_out);									//closing the file
	printf("duplicateit : Copied %d bytes from file %s to %s\n",num_bytes,argv[1],argv[2]);
	return EXIT_SUCCESS;
}