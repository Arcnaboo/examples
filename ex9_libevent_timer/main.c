/**
 *
 * Title: ex11_libevent_timer/main.c, Event Timer using libevent Example
 *
 * Description: This example how to use the event timer from libevent
 *				A timer struct is created and added. Once the time expires,
 *				the callback function is executed.
 *				NOTE: you will need to compile with the -levent library
 *
 * Reference: https://github.com/libevent/libevent
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include <stdio.h>
#include <sys/time.h>
#include <event.h>

/**
 * Event Timer callback function
 */
void event_timer_callback(int fd, short event, void *arg) {

  printf("event timer callback called\n");
}

int main(int argc, const char* argv[]) {
  
	struct event ev;
  	struct timeval tv;

  	tv.tv_sec = 3;		/* Set timeout time to be 3 seconds */
  	tv.tv_usec = 0;

	/* Initialise event library, set/add timer event */
  	event_init();
  	evtimer_set(&ev, event_timer_callback, NULL);
  	evtimer_add(&ev, &tv);

	/* Wait for event to occur */
  	event_dispatch();

  	return 0;
}
