#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/*
fork
exec
clone
pipe
waitpid
exit
sigaction
kill
*/

int main(int argc, char **argv) {
	printf("%d e %d\n", atoi(argv[1]), atoi(argv[2]));

	printf("%d\n", getpgrp());

	//char SHELLSCRIPT[60];
  	//int num, i=4, j=2;
  	//num = sprintf(SHELLSCRIPT, "#/bin/bash\npgrep -P %d", getpgrp());

	//kill(getpgrp(), SIGSEGV);

	//system(SHELLSCRIPT);

	return 0;
}