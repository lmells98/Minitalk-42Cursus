#include "minitalk_bonus.h"

/*	[TODO]:
 *		-	Declare global variable to verify length of message.
*/

/*		TEST SENDING CHAR 'A'
static void	send_test(int server_pid)
{
	//	Sends 'A' ASCII-Character...
	if (server_pid)
	{
//			1 * (2 ^ 0) = 1;
 		kill(server_pid, SIGUSR1);
 		usleep(150);
//			0 * (2 ^ 1) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
//			0 * (2 ^ 2) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
//			0 * (2 ^ 3) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
//			0 * (2 ^ 4) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
//			0 * (2 ^ 5) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
//			1 * (2 ^ 6) = 64;
 		kill(server_pid, SIGUSR1);
 		usleep(150);
//			0 * (2 ^ 7) = 0;
 		kill(server_pid, SIGUSR2);
 		usleep(150);
	}

// 		Where ('1')'s are placed, 
// 		add the calculated values to get ASCII-Character value.
}
*/

static void	send_char_bits(char byte, int pid)
{
	unsigned int	shift;
	int				bit;
	int				err;

	shift = 0;
	bit = 0;
	while (shift < 8)
	{
		bit = (byte >> shift) & 1;
		if (bit == 1)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (err)
			ft_printf("Failed to send signal!\n");
		usleep(200);
		shift++;
	}
}

static void	get_message_binary(char *message, int pid)
{
	unsigned int	i;
	
	i = 0;
	while (message[i] != '\0')
	{
		ft_printf("Got Char - \'%c\'\n", message[i]);
		send_char_bits(message[i], pid);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				server_pid;

	if (argc != 3)
	{
		ft_printf("Error!!! Incorrect Usage\n");
		ft_printf("Use: ./client <pid> message\n");
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	g_Character.size = ft_strlen(argv[2]);
	ft_printf("----------\nString Info\n----------\n");
	ft_printf("String\t= \"%s\"\nlen\t= %d\n----------\n", argv[2], g_Character.size);
//	send_test(server_pid);
	get_message_binary(argv[2], server_pid);
	return (0);
}
