#include<unistd.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
// Show open fds
int main(){
	int fd, res;
	for(fd = 0; fd<10; fd++){
		res = fcntl(fd, F_GETFD);
		printf("FD %d: %d\n", fd, res);
	}
}
