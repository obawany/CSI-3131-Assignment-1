/*--------------------------------------------------------------------

File: dp.c
Student name: 
Student id:   

Description:  Double pipe program.  To pipe the output from the standard
          output to the standard input of two other processes.
          Usage:  dp  <cmd1> : <cmd2> : <cmd3
          Output from process created with cmd1 is piped to
          processes created with cmd2 and cmd3

-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
/* prototypes */
int doublePipe(char **,char **,char **);

/*--------------------------------------------------------------------

File: dp.c

Description: Main will parse the command line arguments into three arrays
         of strings one for each command to execv().
--------------------------------------------------------------------*/

int main(int argc, char *argv[])
{

   int i,j;         /*indexes into arrays */
   char *cmd1[10];  /*array for arguments of first command */
   char *cmd2[10];  /*array for arguments of second command */
   char *cmd3[10];  /*array for arguments of third command */
   if(argc == 1)
   {
     printf("Usage: dp <cmd1 arg...> : <cmd2 arg...> : <cmd3 arg....>\n");
     exit(1);
   }

   /* get the first command */
   for(i=1,j=0 ; i<argc ; i++,j++)
   {
      if(!strcmp(argv[i],":")) break; /* found first command */
      cmd1[j]=argv[i];
   }
   cmd1[j]=NULL;
   if(i == argc) /* missing : */
   {
      printf("Bad command syntax - only one command found\n");
      exit(1);
   }
   else i++;

   /* get the second command */
   for(j=0 ; i<argc ; i++,j++)
   {
      if(!strcmp(argv[i],":")) break; /* found second command */
      cmd2[j]=argv[i];
   }
   cmd2[j]=NULL;
   if(i == argc) /* missing : */
   {
      printf("Bad command syntax - only two commands found\n");
      exit(1);
   }
   else i++;

   /* get the third command */
   for(j=0 ; i<argc ; i++,j++) cmd3[j]=argv[i];
   cmd3[j]=NULL;
   if(j==0) /* no command after last : */
   {
      printf("Bad command syntax - missing third command\n");
      exit(1);
   }

   exit(doublePipe(cmd1,cmd2,cmd3));
}

/*--------------------------------------------------------------------------
  ----------------- You have to implement this function --------------------
  --------------------------------------------------------------------------
Function: doublePipe()

Description:  Starts three processes, one for each of cmd1, cmd2, and cmd3.
          The parent process will receive the output from cmd1 and
          copy the output to the other two processes.
-------------------------------------------------------------------------*/

int doublePipe(char **cmd1, char **cmd2, char **cmd3)
{
	pid_t helperchildpid;
	int fd[2];
	
	pid_t parentpid;
	parentpid = getpid(); //Current process Id 
				//should be > 0

	pipe(fd);
	helperchildpid = fork();	//Child Process id
				//should be 0	
	
	if(helperchildpid == 0){
		//child helper proccess not child a or child b 
		close(fd[0]); //closing reading since this
				//process writes to parent
		
		dup2(fd[1],1); //writing it to parent
		
		close(fd[1]); //done writing so close it 
		
		execvp(*cmd1, cmd1); //executing the first one 
	//what I was doing earlier
	/*
		close(fd[1]); // reading only, closing write
		// Close reading end
		//dup2(fd[1], 1);
		dup2(fd[0],0);
		//close(fd[1]); 
		close(fd[0]);

		execvp(*cmd2, cmd2);
		helperFunc
	
	*/	
	
	}

/*	Ignore this
	else if(pid == -1){
		
		perror("Failed to Fork");
		return 1;

			}
*/
	else {


		// Recieve msg from helpchild
		// copy the msg

		

		pid_t childApid; //pid for child A
		int fdA[2]; 	//fd for child A	
		
		pid_t childBpid; //pid for child B
		int fdB[2];	//fd for child B
		
		pipe(fdA);	//pipe for child A to parent	
		pipe(fdB);	//pipe for child B to parent
		
		char buffer[2048];	//creating buffer
		close(fd[1]);		//close writing

	
	int counter = read(fd[0], buffer, sizeof(buffer));
	char buffer2[counter];
	char buffer3[counter];

	for (int i=0; i<counter; i++){
		
		buffer2[i]=buffer[i];
		buffer3[i]=buffer[i]; 
	
	}
	
		write(fdA[1], buffer2, sizeof(buffer2) );
		write(fdB[1], buffer3, sizeof(buffer3) );

		childApid=fork(); //creating child A here
		
		



		if(childApid==0){ //if successfully child A
			
		close(fdA[1]); //close writing since 
					//child A reads

		dup2(fdA[0],0);//child A reading from pipe
			execvp(*cmd2,cmd2);//execute before close
						
			//close(fd[0]);	//wiritng closed 
	

	}	
		else{
			childBpid=fork();
			if(childBpid==0){
				close (fdB[1]);
				dup2(fdB[0],0);
				//close(fdB[0]);
				execvp(*cmd3, cmd3);
			}
		close(fd[1]);
		//close(fdB[0]);





			

			}
/*
	close(fd[1]);
	close(fd[0]);
	
	pid_t pid2;
	int fd2[2];

	pipe(fd2);
	pid2 = fork();
	
	if(pid2==0){
	
		dup2(fd2[1],1);
		close(fd[1]);
		execvp(*cmd1, cmd1);
	}
	else{
		pid2=fork();
		
		if(pid2==0){
				dup2(fd[0],0);
				close(fd2[0]);
				execvp(*cmd3, cmd3);
			}
		close(fd2[1]);
		close(fd2[0]);
	}
	}	




close(fd[1]); //close reading since
					//child B writes
			
			dup2(fd[0],0);	//child B writing
			execvp(*cmd3,cmd3);//execute before close
			close(fd[0]);	//wiritng closed 
*/

	return 0;
}

}
