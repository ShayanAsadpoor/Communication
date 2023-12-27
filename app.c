#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "encDec.h"
#include <string.h>

int main()
{
  char output[1024] = {0};
  char tmp[1024] = {0};
  
  int fd_write[2], fd_read[2];
  FILE *inpf, *binf, *outf, *chck, *done;
  
  pipe(fd_write);
  pipe(fd_read);

  int pid = fork();

  // 0 -> read
  // 1 -> write
  
  if(pid == 0)
  {

        // producer
    close(fd_read[1]);
    close(fd_write[0]);

    inpf = fopen("filename.inpf","rb");
    binf = fopen("filename.binf","wb");
    done = fopen("filename.done","wb");
    
    int r = 0, step=0;
    
    while((r = fread(tmp,1,64,inpf)) > 0)
    {
       tmp[r] = 0;
     
      //printf(" >>>>> step %d\n", step++);
       //printf("read from file: %s, %d\n",tmp,r);
       appService(tmp, output, 1);
      // printf("read >> app >> %s\n", output);
       dataService(output, tmp, 1);
       // printf("read >> data >> %s\n", tmp);
       phyService(tmp, output, 1);
       
      //printf("read >> phy >> %s\n", output);
       
       write(fd_write[1], output, (r+3)*8);
       fwrite(output,1, (r+3) * 8, binf);
       
    }
    
    fclose(binf);
    fclose(inpf);
    
    while((r = read(fd_read[0], tmp, (64+3)*8)) > 0)
    {
      tmp[r] = 0;
      
      phyService(tmp, output, 0);
      dataService(output, tmp, 0);
      appService(tmp, output, 0);
       
      fwrite(output,1,strlen(output), done);
      
      if(r < ((64+3) * 8)) break;
    }

      
    fclose(done);




  } else
  {

    // consumer    
    
    close(fd_read[0]);    
    close(fd_write[1]);
   
    int r = 0;
    
    outf = fopen("filename.outf","wb");
    chck = fopen("filename.chck","wb");
    
    while((r = read(fd_write[0], tmp, (64+3)*8)) > 0)
    {
       tmp[r] = 0;

       printf("outf: lnk: %s $$\n", tmp);
              
       phyService(tmp, output, 0);
       
       printf("outf: phy: %s $$\n", output);
       
       dataService(output, tmp, 0);
       
       printf("outf: dat: %s $$\n", tmp);
       
       appService(tmp, output, 0);
       
       printf("outf: app: %s $$\n", output);

       toUpperString(output, tmp);
       
       fwrite(tmp, 1, strlen(tmp), outf);
       
       appService(tmp, output, 1);
       dataService(output, tmp,1);
       phyService(tmp, output, 1);
       
       write(fd_read[1], output, strlen(output));
       
       fwrite(output,1, strlen(output), chck);
    }
    
    fclose(outf);
    fclose(chck);
    
    close(fd_read[1]);
    
    wait(NULL);
  }

  
  
  return 0;
}
