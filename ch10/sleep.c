#include "apue.h"

static void sig_alrm(int signo)
{
}

unsigned int sleep(unsigned int seconds)
{
	struct sigaction newact, oldact;
	sigset_t newmask, oldmask, susmask;
	unsigned int unslept;

	newact.sa_handler = sig_alrm;
	sigemtpyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGALRM, &newact, &oldact);

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(seconds);
	susmask = oldmask;
	sigdelset(&susmask, SIGALRM);
	sigsuspend(&susmask);

	unslept = alarm(0);
	sigaction(SIGALRM, &oldact, NULL);
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return unslept;
}
