/**
 *
 * Title: ex1_pthreads/main.c, Pthreads Example
 *
 * Description: This example shows how pthreads are created and used.
 *				Two pthreads are created. Each pthread increments a counter.
 *
 * Reference: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/fork.html
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include <pthread.h>
#include <stdio.h>

/** 
 * This function is run by the second thread 
 */
void *inc_x(void *x_void_ptr) {

	/* increment x to 100 */
	int *x_ptr = (int *)x_void_ptr;

	while(++(*x_ptr) < 100);

	printf("x increment finished\n");

	while(1);
	/* the function must return something - NULL will do */
	return NULL;

}

/** 
 * This function is run by the second thread 
 */
void *inc_z(void *z_void_ptr) {

	/* increment x to 100 */
	int *z_ptr = (int *)z_void_ptr;

	while(++(*z_ptr) < 100);

	printf("z increment finished\n");

	while(1);

	/* the function must return something - NULL will do */
	return NULL;

}

int main() {

	int x = 0, y = 0, z = 0;
	pthread_t inc_x_thread;			/* this variable is our reference to the second thread */
	pthread_t inc_z_thread;			/* this variable is our reference to the second thread */

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* create a second thread which executes inc_x(&x) */
	if(pthread_create(&inc_z_thread, NULL, inc_z, &z)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* increment y to 100 in the first thread */
	while(++y < 100);

	printf("y increment finished\n");

	/* wait for the second thread to finish */
	if(pthread_join(inc_x_thread, NULL)) {

		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d, y: %d\n", x, y);

	return 0;

}


