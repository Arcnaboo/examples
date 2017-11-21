/**
 *
 * Title: ex13_mutex/main.c, Mutex Example
 *
 * Description: This example shows how mutexes are created and used.
 *
 * Reference: http://www.csc.villanova.edu/~mdamian/threads/posixsem.html
 *
 * Modified by: MD & VS
 *
 * Date: 26/8/2016
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t countmutex = PTHREAD_MUTEX_INITIALIZER;		/* Counter mutex */
int count;

/** 
 * Increment thread 
 */
void incrementer(void) {
	
	while(1) {

		/* Lock Mutex */
		pthread_mutex_lock (&countmutex);
		
		/* Increment counter */
		count += 5;	
        printf("Incremented counter %d\n", count);

		/* Unlock Mutex */
		pthread_mutex_unlock (&countmutex);

		/* wait 5s */
		sleep(5);
	}

}

/** 
 * Decrement thread 
 */
void decrementer(void) {

	while(1) {

		/* Lock Mutex */
		pthread_mutex_lock (&countmutex);

		/* Decrement counter */
		count--;
        printf("Decremented counter %d\n", count);

		/* Wait for semaphore to occur */
		pthread_mutex_unlock (&countmutex);

		/* wait 1s */
		sleep(1);
	}

}

int main() {

	pthread_t inc_thread;		
	pthread_t dec_thread;

	/* Initialise mutex.*/
	pthread_mutex_init(&countmutex, NULL);
	
	/* create the inrementer thread */
	if(pthread_create(&inc_thread, NULL, (void *)incrementer, NULL)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* create the decrementer thread */
	if(pthread_create(&dec_thread, NULL, (void *)decrementer, NULL)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}


	/* wait */
	while(1);

	return 0;

}


