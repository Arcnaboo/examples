/**
 *
 *****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: fifoserver.c
 *****************************************************************************
 *
 * Title: ex10_fifo/fifoserver.c, FIFO Server Example
 *
 * Description: This example shows how a FIFO server works.
 *
 * Reference: http://www.tldp.org/LDP/lpg/node15.html
 *
 * Modified by: MD & VS
 *
 * Date: 13/8/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/stat.h>

#define FIFO_FILE       "MYFIFO"

int main(void) {

	FILE *fp;
	char readbuf[80];

	/* Create the FIFO if it does not exist */
	umask(0);
	mknod(FIFO_FILE, S_IFIFO|0666, 0);

	/* Wait to receive strings */
	while(1) {

		fp = fopen(FIFO_FILE, "r");		/* Open FIFO */
		fgets(readbuf, 80, fp);			/* Read from FIFO */
		printf("Received string: %s\n", readbuf);	
		fclose(fp);						/* Close FIFO  */
	}

	return(0);
}



