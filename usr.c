#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DEST_SIZE 300

int main(int argc, char* argv[])
{
   char  usr_param[DEST_SIZE];
   char  usr_pid[DEST_SIZE];
   char  dest[DEST_SIZE];

   
   if(argc==1){
     printf("Right Usage:\n-all prints some information (process id and its argument/s) about all processes\n-p takes process id and prints the details of it\n-k takes process id\n");
   }
   else if(argc==2){
      sprintf(usr_param,argv[1]);
   }
   else if(argc==3){
      sprintf(usr_param,argv[1]);
      sprintf(usr_pid,argv[2]);
   }
   else{
      printf("Something went wrong..");
   }


    long int return_val = syscall(335, usr_param, usr_pid,dest);
    printf("%s\n",dest);

return return_val;
}