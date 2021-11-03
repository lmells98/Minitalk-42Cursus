/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:59 by lmells            #+#    #+#             */
/*   Updated: 2021/11/03 11:21:02 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*			** GLOBAL STRUCT **
*/
t_Character	g_Character;

/*	[TODO]:
 *		-	Write a function that will handle signal from server.
 *		-	Confirms successful bytes sent.
*/
static void	confirm_server(int sig)
{
	(void)sig;
	if (sig == SIGUSR2)
	{
		ft_printf("Message sent successfully!\n");
		exit(EXIT_SUCCESS);
	}
}

/*	** SEND BINARY DATA **
 *
 *		-	Take in a byte from the string and the server's process ID.
 *		-	Use bitshifting and bitwise operator to get each bit from right to
 *			left. (Least Significent Bit goes first).
 *		-	Bit is assigned 1 or 0 depending on position of bit in byte
 *		-	Use kill() to send a signal to the process ID. Returns 0 on
 *			succesful send. -1 if it errors.
 *		-	Shift is incremented to apply (2 ^ shift).
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
		ft_printf("%i", bit);
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

/*	** Main Structure **
 *
 *		-	Sigaction Struct
 *			-	Sigaction handler is used to set the function we want to handle
 *				the signal received from a process.
 *		-	Get the server's process ID from arguments.
 *		-	While the process is still active. Any signal received from SIGUSR2 will be
 *			processed by the s_client sigaction struct.
 *		-	Iterate through each byte of the string and send the binary data to
 *			the server.
 *		-	Pauses the instructions, waiting for signal confirmation from the
 *			server.
*/
int	main(int argc, char **argv)
{
	unsigned int		server_pid;
	unsigned int		i;
	struct	sigaction	s_client;

	if (argc == 3)
	{
		s_client.sa_handler = &confirm_server;
		server_pid = ft_atoi(argv[1]);
		i = 0;
		while (1)
		{
			sigaction(SIGUSR2, &s_client, NULL);
			while (i < ft_strlen(argv[2]))
			{
				send_char_bits(argv[2][i], server_pid);
				i++;
			}
			pause();
		}
	}
	else
	{
		ft_printf("Error!!! Incorrect Usage\n");
		ft_printf("Use: ./client <pid> message\n");
	}
	return (0);
}
