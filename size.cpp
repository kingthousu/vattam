#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;

enum errors {
  DEFAULT,
  ARG_ERR,
  FILE_OPEN,
  FILE_CLOSE,
};

off_t TotalSize = 0;
 
enum errors err_code = DEFAULT;

static int printSize(int fd) {
	struct stat fileStat;
	if(fstat(fd,&fileStat) < 0) {   
		return -1; // some error with fstat()
	}
    TotalSize = TotalSize + fileStat.st_size;
	cout<< " : "<<fileStat.st_size<<" bytes"<<endl;
    return 0;
}

static int getFileDetails(const char *fname) {
  int fd, success=1;

  if ((fd = open(fname, O_RDONLY)) == -1){
    err_code = FILE_OPEN;
    return -1;
  }
  cout << fname ;
  success = printSize(fd);

  if (close(fd) != 0){
  	err_code = FILE_CLOSE;
    return -1;
	}
  return success;

}

int main(int argc , char** argv) {
  int i;
  if (argc < 2) {
      err_code = ARG_ERR;
      goto error;
  } else {
    for (i = 1; i < argc; i++) {
      if (getFileDetails(argv[i]) != 0)
        goto error;
    }
  }
  if(argc>2){
      cout << "Total Size :" <<TotalSize <<"bytes " <<endl;
  }
  return 0;
 
error:
    switch (err_code) {

    case FILE_OPEN:
      cout<<"File Error: No such file or directory"<<endl;
      break;
    case ARG_ERR:
      cout<<"Argument Error: requires one filename argument"<<endl;
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