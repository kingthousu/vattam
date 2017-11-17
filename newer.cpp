#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
using namespace std;

enum options {
	DEF_OPT,
	ACC_TIME,
	MOD_TIME,
	CHE_TIME,
};
enum errors {
  DEFAULT,
  ARG_ERR,
  OPT_ERR,
  FILE_OPEN,
  FILE_CLOSE,
};

off_t TotalSize = 0;
time_t ref_time = 0;
 
enum errors err_code = DEFAULT;
enum options t_option  = DEF_OPT;
int NEW = 0;
static int findNewer(int fd , char pos) {
	struct stat fileStat;
	if(fstat(fd,&fileStat) < 0) {   
		return -1; // some error with fstat()
	}
	
    switch(t_option){
		case ACC_TIME:if (fileStat.st_atime > ref_time) {
				        NEW = pos;
				        ref_time = fileStat.st_atime;
				      }
					  break;
		case MOD_TIME:if (fileStat.st_mtime > ref_time) {
				        NEW = pos;
				        ref_time = fileStat.st_mtime;
				      }
					  break;
		case CHE_TIME:if (fileStat.st_ctime > ref_time) {
				        NEW = pos;
				        ref_time = fileStat.st_ctime;
				      }
					  break;
		default:
				 err_code = OPT_ERR;
				 return -1;
				 break;
	}
    
    
    return 0;
}

static int getFileDetails(const char *fname, char pos) {
  int fd, success=1;

  if ((fd = open(fname, O_RDONLY)) == -1){
    err_code = FILE_OPEN;
    return -1;
  }

  success = findNewer(fd ,pos);

  if (close(fd) != 0){
  	err_code = FILE_CLOSE;
    return -1;
	}
  return success;

}

int main(int argc , char** argv) {
  int i;
  if (argc != 4) {
      err_code = ARG_ERR;
      goto error;
  } else {
    if(strcmp(argv[1],"-a")==0){
		t_option = ACC_TIME;
	}
	if(strcmp(argv[1],"-m")==0){
		t_option = MOD_TIME;
	}
	if(strcmp(argv[1],"-c")==0){
		t_option = CHE_TIME;
	}
  	
    for (i = 2; i < argc; i++) {
      if (getFileDetails(argv[i], i) != 0)
        goto error;
    }
  }
  
   
  cout << argv[NEW]  <<endl; //printing the newest file according with the option 
 
  return 0;
 
error:
    switch (err_code) {

    case FILE_OPEN:
      cout<<"File Error: No such file or directory"<<endl;
      break;
    case ARG_ERR:
      cout<<"Argument Error: requires option and filename arguments"<<endl;
      break;
     case OPT_ERR:
      cout<<"Option Error: valid options are -a |-c |-m"<<endl;
      break;
    case FILE_CLOSE:
      cout<<"Error:  Unable to close file"<<endl;
      break;
    default:
      cout<<"Error:  Unknown error happend"<<endl;
      break;
    }
  return 1;

}