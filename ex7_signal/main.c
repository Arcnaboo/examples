/**
 *
 * Title: ex3_signal/main.c, Signal handling example
 *
 * Description: This example shows how to handle a signal using sigaction.
 *				There are three ways to handle signals with sigaction, it
 *				can call a handler with one argument (signal number received),
 *				call a handler with three arguments (second contains information
 *				on the sending process), or it can ignore the signal without
 *				executing a handler.
 *
 *
 * Author: AS
 *
 * Date: 05/08/2017
 */

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>	/* needed for getpid() */


static void usr1ActSimple(int sig);
static void usr2ActWithInfo(int sig, siginfo_t *siginfo, void *context);

int main(int argc, char **argv) {

	/* Initialise structs for signal handling behaviour */
	struct sigaction usr1Act;
	struct sigaction usr2Act;
	struct sigaction pipeAct;
	int pid;
	unsigned int remaining;
	memset(&usr1Act, 0, sizeof(struct sigaction));
	memset(&usr2Act, 0, sizeof(struct sigaction));
	memset(&pipeAct, 0, sizeof(struct sigaction));

	pid = getpid();

	/* Sets a handler which takes one argument for SIGUSR1 */
	usr1Act.sa_handler = usr1ActSimple;
	/* The SA_RESTART flag means that certain primitive functions (such as open,
	 * read or write) are restarted if interrupted.  Otherwise they will return
	 * failure with an EINTR error code.*/
	usr1Act.sa_flags = SA_RESTART;
	/* Apply sigaction struct to signal. */
	sigaction(SIGUSR1, &usr1Act, NULL);


	/* For a handler with three arguments sa_sigaction field is used and
	 * the SA_SIGINFO flag must be used. */
	usr2Act.sa_sigaction = &usr2ActWithInfo;
	usr2Act.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR2, &usr2Act, NULL);


	/* SIG_IGN is used instead of a function pointer to just ignore a signal. */
	pipeAct.sa_handler = SIG_IGN;
	pipeAct.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &pipeAct, NULL);

	printf("To test the behaviour of the signal handling, \
			run one of the following commands from another window:\n");
	printf("kill -s USR1 %d\n", pid);
	printf("kill -s USR2 %d\n", pid);
	printf("kill -s PIPE %d\n", pid);

	/* Keep main loop running */
	for (;;) {
		printf("Going to sleep\n");
		/* sleep() returns zero if the requested time has elapsed, or the
		 * number of seconds left to sleep, if the call was interrupted by a
		 * signal handler. */
		remaining = sleep(30);
		printf("Seconds remaining on sleep: %d\n", remaining);
	}
}

/*
 * Signal handlers below.  Note that printf should not normally be used
 * in a signal handler (or any other interrupt handler)
 */

static void usr1ActSimple(int sig) {
	printf("Received signal %d\n", sig);
}

static void usr2ActWithInfo(int sig, siginfo_t *siginfo, void *context) {
	printf("Received signal %d from PID: %ld, UID: %ld\n", sig,
			(long)siginfo->si_pid, (long)siginfo->si_uid);
}

