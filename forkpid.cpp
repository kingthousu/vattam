#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
  {
    pid_t pid;
    pid=fork();
    if(pid==-1){
            perror("fork failure");
            exit(EXIT_FAILURE);
    }
    else if(pid==0){
			cout<<"-----child process-----"<<endl;
            printf("process id =%d and parent process id =%d\n",getpid(),getppid()); 
            
    }
    else{
			//cout<<""<<endl;
            printf("-----parent process----- \n process id =%d and process id of parent process = %d \n",getpid(),getppid());
            sleep(0);
    }
    exit(EXIT_SUCCESS);
  }