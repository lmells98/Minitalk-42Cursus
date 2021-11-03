/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:59 by lmells            #+#    #+#             */
/*   Updated: 2021/11/03 13:00:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/* **GLOBAL STRUCT**
*/
t_character	g_character;

/*	**INITIALISE SERVER**
 *		-	Write a function that will Initialise all struct variables.
 *		-	Server startup messages will print here.
 */
static void	init_struct(void)
{
	g_character.byte = 0;
	g_character.shift = 0;
	ft_printf("---------- Launching Minitalk Server ----------\n");
	ft_printf("\t\tServer PID : %d\n", getpid());
	ft_printf("Launch the client in seperate window to start talking\n");
	ft_printf("-----------------------------------------------\n");
}

/*	**BUILD BYTE FROM BINARY**
 *		-	Shifts each bit received by the client by applying (2 ^ shift).
 *		-	Append that values that the 1 bit represents on the binary table.
 *		-	Once 8 Shifts have been performed (128-bit), display the char to the
 *			screen.
 *		-	if the byte isnt ASCII, it will be thrown onto the stack, therefore
 *			allowing the next byte(s) to determine the Unicode Representation.
 *			This is because we are receiving the binary data Backwards.
 *		-	Iterate through 1 more time to confirm end of message. Print new
 *			line on server output ready for a new message.
 *		-	Send signal with kill() back to the client.
*/
static void	build_message(int bit, t_character *g_char, pid_t client)
{
	g_char->byte += bit << g_char->shift;
	g_char->shift++;
	if (g_char->shift == 8)
	{
		if (!g_char->byte)
		{
			ft_putstr_fd("\n", 1);
			kill(client, SIGUSR2);
		}
		ft_putchar_fd(g_char->byte, 1);
		g_char->byte = 0;
		g_char->shift = 0;
	}
}

/*	**SIGNAL HANDLER**
 *		-	Receve signal from client.
 *		-	Store the process ID of the sender.
 *		-	Take the signal and send it to a function.
 *		-	This function will build a byte that can be displayed
 *			as its Uni-Code Character Representation.
*/
static void	receive_signal(int bit, siginfo_t *info, void *context)
{
	(void)context;
	if (bit == SIGUSR1)
		bit = 1;
	else if (bit == SIGUSR2)
		bit = 0;
	build_message(bit, &g_character, info->si_pid);
}

/*	**MAIN STRUCTURE**
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
