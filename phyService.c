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
   int len = 0;
   
   if(argc == 3)
   {
      len = strlen(argv[2]);

      if(argv[1][0] == '-' && argv[1][1] == 'd')
      { 
        if(len % 8 == 0)
	for(int i=0;i<len;i+=8)
	{
		if(phyDecode(&argv[2][i], output) == OK)
		{
		    write(1,output,strlen(output));
		} else
		{
		  write(1,"-ERROR-!",8);
		}
        }
      } else
      if(argv[1][0] == '-' && argv[1][1] == 'e')
      {
        
          for(int i=0;i<len;i++)
          {
                   
		 if(phyEncode(&argv[2][i], output) == OK)
		 {
		    write(1,output,strlen(output));
		 }
          }
      } else
      {

      }
      
   }
}

int phyEncode(char *input, char *output)
{
   char ch = input[0];
   int  bit = 0;
   int  no1 = 1;
   
   ch = ch & 0x7f;
   output[8] = 0;
   
   for(int j=0;j<8;j++)
   {
     if(j < 7)
     {
       bit = (ch >> j) & 0x01;
       no1 = no1 ^ bit;
     } else
       bit = no1;
       
     output[7-j] = '0' + bit;
   }
   
   return OK;
}


int phyDecode(char *input, char *output)
{
   int no1 = 0;
   int bit = 0;
   char ch = 0;
   
	for(int j=0;j<8;j++)
	{
	 bit = input[j] == '1' ? 1 : 0;
	 if(j > 0)
	 {
	   ch |= bit << (7-j);
	 }
	 if(bit == 1) no1++;
	}

	if(no1 % 2 == 0)
	{
	 output[0] = 0;
	 return ERROR;
	} else
	{
	 output[0] = ch;
	}

	return OK;
}


