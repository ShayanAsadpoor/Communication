#include "encDec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLEN 64
#define ERROR 1
#define OK    0

int main(int argc, char *argv[])
{
   char output[MAXLEN*8] = {0};
   if(argc == 3)
   {
      if(argv[1][0] == '-' && argv[1][1] == 'd')
      { 
        if(dataDecode(argv[2], output) == OK)
        {
            write(1,output,strlen(output));
        } else
        {
           write(1,"-ERROR-!",8);
        }
      } else
      if(argv[1][0] == '-' && argv[1][1] == 'e')
      {
         if(dataEncode(argv[2], output) == OK)
         {
            write(1,output,strlen(argv[2])+3);
         } else
         {
	   write(1,"-ERROR-!",8);
         }
      } else
      {

      }
   }
}

int dataEncode(char *input, char *output)
{
   int len = strlen(input);
   
   if(len == 0 || len > MAXLEN)
   {
      return ERROR;
   } else
   {
       output[0] = 22;
       output[1] = 22;
       output[2] = (char)(len & 0x7f);
       
       for(int i=0;i<len;i++)
       {
         output[3+i] = input[i];
       }
       
       output[3+len] = 0;
       
       return OK;
   }
}


int dataDecode(char *input, char *output)
{
    int len = strlen(input);
    
    output[0] = 0;
    
    if(len == 0 || len < 4)
    {
       return ERROR;
    } else
    {
       int flen = input[2] & 0x7f;
       
       if(flen < 1 || flen > MAXLEN)
        return ERROR;
        
       if(input[0] == 22 && input[1] == 22 && (flen+3) == len )
       {
         for(int i=0;i<flen;i++)
         {
            output[i] = 0;
            output[i] = input[3+i] & 0x7f;
         }  
         
         output[flen] = 0;
         
         return OK;
         
       } else
        return ERROR;
    }
}
