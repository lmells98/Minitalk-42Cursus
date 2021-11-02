/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:59 by lmells            #+#    #+#             */
/*   Updated: 2021/11/02 12:08:55 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_Character	g_Character;
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
	ft_printf("\n");
}

int	main(int argc, char **argv)
{
	unsigned int		server_pid;
	unsigned int		i;
	struct	sigaction	s_client;

	if (argc == 3)
	{
		s_client.sa_handler = &confirm_server;
		server_pid = ft_atoi(argv[1]);
		ft_printf("----------\nDEBUG INFO\n----------\n");
		ft_printf("Client\t= %d\n", getpid());
		ft_printf("String\t= \"%s\"\nlen\t= %d\n", argv[2], ft_strlen(argv[2]));
//		send_test(server_pid);
		i = 0;
		while (1)
		{
			sigaction(SIGUSR2, &s_client, NULL);
			while (1 < ft_strlen(argv[2]))
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
