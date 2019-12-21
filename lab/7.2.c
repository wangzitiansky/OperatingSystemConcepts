#include <stdio.h>
#include <signal.h.h>

static void sig_usr(int);

int main(int argc, char const *argv[])
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		printf("can not catch SIGUSER2\n");
		exit(1);
	}
	if (signal)
	{
		/* code */
	}
	return 0;
}