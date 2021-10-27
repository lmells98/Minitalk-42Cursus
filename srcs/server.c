#include "../includes/minitalk.h"

/* 	[TODO]:
 *  	-	Take in the value assigned when a SIGUSR signal
 *  		is received.
 *  	-	Store it in a bit array.
 *  	-	Convert bit array to decimal
 *  	-	Display char decimal to screen
*/
static char	build_bits(int byte)
{
	static char 	bits;
	unsigned int	shift;

	/*	[TODO]:
	 *		-	Figure out Bit shifting upwards.
         *              -       start from 0, work up and don't check for 1
	*/ 	
	shift = 8;
	if (shift > 0)
	{
		bits = (byte << shift) & 1;
		ft_printf("S=%u - By=%i - Bi=%i\n", shift, byte, bits);
		shift--;
	}
	return (bits);
}

static void	receive_bits(int sig)
{
	static int		count;
	static char		byte;

	if (!count)
		count = 0;
	count += 1;
	ft_printf("C=%d", count);
	write(1, "\n", 1);
	if (sig == SIGUSR1)
		byte = build_bits('1');
	else if (sig == SIGUSR2)
		byte = build_bits('0');
	if (count == 8)
	{
		ft_printf("End of Byte\n");
		write(1, &byte, ft_strlen(&byte));
		byte = 0;
		count = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID %u\n", getpid());
	ft_printf("Run Client in another window to talk...\n");
	ft_printf("Use: ./client <pid> \"message\"\n");
	while (1)
	{
		signal(SIGUSR1, receive_bits);
		signal(SIGUSR2, receive_bits);
		pause();
	}
	return (0);
}
