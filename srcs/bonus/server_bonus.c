#include "minitalk_bonus.h"

t_Character	g_Character;

static void	build_message(int bit, t_Character *g_char)
{
	static char	*message;

	if (!message)
		message = ft_strdup("");
	g_char->byte += bit << g_char->shift;
	g_char->shift++;
	if (g_char->shift == 8)
	{
		message = ft_append_char(message, g_char->byte);
		g_char->byte = 0;
		g_char->shift = 0;
		g_char->size += 1;
	}
	if (g_char->size && g_char->size == ft_strlen(message))
	{
		ft_putstr_fd(message, 1);
		free(message);
		message = NULL;
		g_char->size = 0;
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
	g_Character.client_pid = info->si_pid;
	//g_Character.client_pid = 123;
	if (bit == SIGUSR1)
		bit = 1;
	else if (bit == SIGUSR2)
		bit = 0;
	build_message(bit, &g_Character);
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
	
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = receive_signal;
	g_Character.byte = 0;
	g_Character.shift = 0;
	g_Character.size = 0;
	g_Character.client_pid = 0;
	ft_printf("Server PID: %u\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
