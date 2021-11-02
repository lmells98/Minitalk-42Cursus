/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:59 by lmells            #+#    #+#             */
/*   Updated: 2021/11/02 12:15:30 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_Character	g_Character;

/*	[TODO];	** FUNTION**
 *		-	Write a function that will Initialise all struct variables.
 *		-	Server startup messages will print here.
 */ 
static void	init_struct(void)
{
	g_Character.byte = 0;
	g_Character.shift = 0;
	g_Character.size = 0;
	ft_printf("---------- Launching Minitalk Server ----------\n");
	ft_printf("\t\tServer PID : %d\n", getpid());
	ft_printf("Launch the client in seperate window to start talking\n");
	ft_printf("-----------------------------------------------\n");
}

static void	build_message(int bit, t_Character *g_char, pid_t client)
{
	g_char->byte += bit << g_char->shift;
	g_char->shift++;
	g_char->size += 1;
	if (g_char->shift == 8)
	{
		if (!g_char->byte)
		{
			ft_putstr_fd("\n", 1);
			kill(client, SIGUSR2);
		}
		ft_putchar_fd(g_char->byte, 1);
		g_char->size += 0;
		g_char->byte = 0;
		g_char->shift = 0;
	}
}

/*	[TODO]:
 *		-	Receve signal from client.
 *		-	Store the process ID of the sender.
 *		-	Take the signal and send it to a function.
 *		-	This function will build a byte that can be displayed
 *			as its Uni-Code Character Representation.
*/ 
static void	receive_signal(int bit, siginfo_t *info, void *context)
{
	(void)context;
	//g_Character.client_pid = 123;
	if (bit == SIGUSR1)
		bit = 1;
	else if (bit == SIGUSR2)
		bit = 0;
	build_message(bit, &g_Character, info->si_pid);
}

/*	[TODO]:
 *		-	Declaring sigaction struct allows us to carry extra information
 *			about the established signal
 *				** Sigaction Flags **
 *				-	siginfo 	- Carrys Process Information From Sender.
 *				-	sigaction	- Carrys Function for Signal Processing.
 *		-	Initialise global struct variables.
 *		-	Display the server's process ID.
 *		-	Set actions for user defined signals.
 *		-	Pause, ready to receive a message from the client.
 *
*/ 
int	main(void)
{
	struct sigaction	sa;
	
	ft_memset(&sa, '\0', sizeof(sa));
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &receive_signal;

	init_struct();
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
