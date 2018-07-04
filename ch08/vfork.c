#include "apue.h"

int globvar = 6;  /* external variable in initialized data */

int main(void)
{
	int var;  /* automatic variable on the stack */
	pid_t pid;
	
	var = 88;
	printf("before fork\n");
	if ((pid = vfork()) < 0)
		err_sys("vfork error");
	else if (pid == 0) {
		globvar++;
		var++;
		exit(0);
	}

	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
	exit(0);
}