#include "minitalk.h"

/* 	TODO[Leighton]:
 *  	-	Take in the value assigned when a SIGUSR signal
 *  		is received.
 *  	-	Store it in a bit array.
 *  	-	Convert bit array to decimal
 *  	-	Display char decimal to screen
*/ 	

void	receive_bits(int sig)
{
	if (sig == SIGUSR1)
		write(1, "1", 1);	
	else if (sig == SIGUSR2)
		write(1, "0", 1);	
	else
		write(1, "No Signal Detected!\n", 20);
}

int	main(void)
{
	printf("Server PID %u\n", getpid());
	printf("Run Client in another window to talk...\n");
	printf("Use: ./client <pid> \"message\"\n");
	while (1)
	{
		signal(SIGUSR1, receive_bits);
		signal(SIGUSR2, receive_bits);
		pause();
	}
	return (0);
}
