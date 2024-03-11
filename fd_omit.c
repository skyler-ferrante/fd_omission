#include<unistd.h>

int main(){
	close(1); close(2);
	execve("./show_open", NULL, NULL);
}
