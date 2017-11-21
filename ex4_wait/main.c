/**
 *
 * Title: ex1_pthreads/main.c, Wait Example
 *
 * Description: This example shows how wait is used to put a process to sleep.
 *
 * Reference: 	https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/wait.html
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include <stdlib.h>	/* needed to define exit() */
#include <unistd.h>	/* needed for fork() and getpid() */
#include <errno.h>	/* needed for errno */
#include <stdio.h>	/* needed for printf() */

void child(void);	/* the child calls this */
void parent(int pid);	/* the parent calls this */
int pid;	/* process ID */

int main(int argc, char **argv) {
	
	/* Create child process */
	switch (pid = fork()) {

		case 0:		/* a fork returns 0 to the child */
			child();
			break;

		default:	/* a fork returns a pid to the parent */
			parent(pid);
			break;

		case -1:	/* something went wrong */
			perror("fork");
			exit(1);
	}

	exit(0);
}

/** 
 * Child Process 
 */
void child(void) {

	printf("About to run ls\n");

	/* Execute 'ls' command */
	execlp("ls", "ls", "-aF", "/", (char*)0);
	perror("execlp");	/* if we get here, execlp failed */
	exit(1);
}

/** 
 * Parent Process 
 */
void parent(int pid) {

	int got_pid, status;

	/* Wait until child process has finished */
	while (got_pid = wait(&status)) {   /* go to sleep until something happens */

		/* wait woke up */
		if (got_pid == pid)
			break;	/* this is what we were looking for */

		if ((got_pid == -1) && (errno != EINTR)) {
			/* an error other than an interrupted system call */
			perror("waitpid");
			return;
		}

	}

	if (WIFEXITED(status))	/* process exited normally */
		printf("child process exited with value %d\n", WEXITSTATUS(status));

	else if (WIFSIGNALED(status))	/* child exited on a signal */
		printf("child process exited due to signal %d\n", WTERMSIG(status));

	else if (WIFSTOPPED(status))	/* child was stopped */
		printf("child process was stopped by signal %d\n", WIFSTOPPED(status));
}
