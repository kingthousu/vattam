#include<iostream>
#include <dirent.h>

using namespace std;
int main()
{
	DIR *cur;
	dirent *mypdir;
	
	cur=opendir(".");
	int i=1;
	while((mypdir=readdir(cur)))
	{
		cout<<mypdir->d_name<<endl;
		i++;
	}
	closedir(cur);
	return 0;
}
