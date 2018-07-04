#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)  /* POSIX-style abort() function */
{
	sigset_t mask;	
	struct sigaction action;

	/* Caller can't ignore SIGABRT, if so reset to default */
	sigaction(SIGABRT, NULL, &action);
	if (action.sa_handler == SIG_IGN) {
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if (action.sa_handler == SIG_DFL)
		fflush(NULL);
	
	/* Caller can't block SIGABRT; make sure it's unblocked */
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	
	/* If we're here, process caught SIGABRT and returned */
	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}
