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
        if(appDecode(argv[2], output) == OK)
        {
            write(1,output,strlen(output));
        } else
        {
          write(1,"-ERROR-!",8);
        }
      } else
      if(argv[1][0] == '-' && argv[1][1] == 'e')
      {
         if(appEncode(argv[2], output) == OK)
         {
            write(1,output,strlen(output));
         }else
        {
          write(1,"-ERROR-!",8);
        }
      } else
      {

      }
   }
}


int appEncode(char *input, char *output)
{
   for(int i=0;input[i] != 0;i++)
   {
     output[i] = input[i];

   }
    
    return OK;
}


int appDecode(char *input, char *output)
{
   for(int i=0;input[i] != 0;i++)
   {
     output[i] = input[i];
   }
    
    return OK;

}



