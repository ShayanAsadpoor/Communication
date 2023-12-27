#include "encDec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLEN 64
#define ERROR 1
#define OK    0

int runService(char *input, char *output, int encode, char *serviceName)
{
   int fd[2];
 
   
   //sprintf(inp,"'%s'", input);
   
   pipe(fd);

   int pid = fork();
   
   if(pid == 0)
   {
      close(fd[0]);
      close(1);
      dup2(fd[1],1);
	   if(encode)
	   {
	      execlp(serviceName,serviceName,"-e",input,NULL); 
	   } else
	   {
	      execlp(serviceName,serviceName,"-d",input,NULL); 
	   }
   } else
   {
      char buff[2048] = {0};
      
      close(fd[1]);
      wait(NULL);
      
      int r = read(fd[0],buff,2048);
      close(fd[0]);
      buff[r] = 0;
      memcpy(output, buff, r+1);
      
   }
   
   return OK;

}


int phyService(char *input, char *output,  int encode)
{
   return runService(input, output, encode, "./phyService");
}



int dataService(char *input, char *output,int encode)
{
  return runService(input, output, encode, "./dataService");
}



int appService(char *input, char *output,int encode)
{
  return runService(input, output, encode, "./appService");
}

void toUpperString(char *input, char *output)
{
   int i=0;
   
   for(i=0;i<strlen(input);i++)
   {
      output[i] = input[i] >= 'a' && input[i] <= 'z' ? (input[i] - 'a' + 'A') : input[i];
   }
   
   output[strlen(input)] = 0;
}


