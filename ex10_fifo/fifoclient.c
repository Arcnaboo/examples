/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: fifoclient.c
 *****************************************************************************
 *
 * Title: ex10_fifo/fifoclient.c, FIFO client Example
 *
 * Description: This example shows how a FIFO client works.
 *				Sends command line string to FIFO e.g. fifoclient mystring
 *
 * Reference: http://www.tldp.org/LDP/lpg/node15.html
 *
 * Modified by: MD & VS
 *
 * Date: 13/8/2016
 */

#include <stdio.h>
#include <stdlib.h>

#define FIFO_FILE       "MYFIFO"

int main(int argc, char *argv[]) {
	FILE *fp;

	/* Check if send string has been included on the command line */
	if ( argc != 2 ) {
		printf("USAGE: fifoclient [string]\n");
		exit(1);
	}

	/* Open FIFO */
	if((fp = fopen(FIFO_FILE, "w")) == NULL) {
		perror("fopen");
		exit(1);
	}

	/* Send command line string to FIFO */
	fputs(argv[1], fp);

	/* Close FIFO */
	fclose(fp);
	return(0);
}
matt
