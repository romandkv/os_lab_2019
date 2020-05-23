#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/* 
 * или чтобы увидеть родителя и его зомби-процесс
 * ps -e --format pid,ppid,stat,cmd
 */
int main()
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid > 0) {
		/* Это родительский процесс — делаем минутную паузу. */
		sleep(60);
		wait(NULL);
	} else {
		printf("I am zombie\n");
		exit(0);
	}
	return 0;
}