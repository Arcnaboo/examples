/**
 *
 * Title: ex6_pipe/main.c, Pthreads Example
 *
 * Description: This example shows how pipe is created and used.
 *
 * Reference: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/pipe.html
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	
	int n;
	int fd[2];
	char buf[1025];
	char *data = "hello... this is sample data";

	/* Create pipe and write string */
	pipe(fd);
	write(fd[1], data, strlen(data));

	/* Read from pipe */
	if ((n = read(fd[0], buf, 1024)) >= 0) {
		buf[n] = 0;	/* terminate the string */
		printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
	}
	
	else {
		perror("read");
		exit(0);
	}

	return 0;
}
