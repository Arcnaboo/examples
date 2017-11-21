/**
 *
 * Title: ex11_semaphore/main.c, Semaphore Example
 *
 * Description: This example shows how semaphores are created and used.
 *
 * Reference: http://www.csc.villanova.edu/~mdamian/threads/posixsem.html
 *
 * Modified by: MD & VS
 *
 * Date: 26/8/2016
 */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>


sem_t sem;

/** 
 * Sender thread 
 */
void sender(void) {
	
	while(1) {

		/* Post a semaphore */
		if (sem_post(&sem) == -1) {
        	printf( "sem_post() failed\n");
		}

		printf("semaphore posted\n");

		/* wait 5s before posting the next semaphore */
		sleep(5);
	}

}

/** 
 * Receiver thread 
 */
void receiver(void) {

	while(1) {


		/* Wait for semaphore to occur */
		if (sem_wait(&sem) == 0) {;
			printf("received semaphore\n");
		}
	}

}

int main() {

	pthread_t sender_thread;		
	pthread_t receiver_thread;

	/* Initialise semaphore with initial value of 0.*/
	if (sem_init(&sem, 0, 0) == -1) {
    	printf("sem_init error");
	}
	
	/* create the sender thread */
	if(pthread_create(&sender_thread, NULL, (void *)sender, NULL)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	/* create the receiver thread */
	if(pthread_create(&receiver_thread, NULL, (void *)receiver, NULL)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;
	}


	/* wait */
	while(1);

	return 0;

}


