#include "minitalk_bonus.h"

/*	[TODO]:
 *		-	Declare Global Variable to verify length of message.
*/ 

static char	*append_char(char *old_arr, char byte)
{
	unsigned int	i;
	char			*new;

	new = (char *)malloc((ft_strlen(old_arr) + 2) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (old_arr && old_arr[i] != '\0')
	{
		new[i] = old_arr[i];
		i++;
	}
	new[i] = (unsigned int)byte;
	new[i + 1] = '\0';
	free(old_arr);
	return (new);
}

static void	build_bytes(int bit, t_Character *g_char)
{
	static char		*message;

	if (!message)
		message = ft_strdup("");
	if (bit == 0 || bit == 1)
	{
		g_char->byte += bit << g_char->shift;
		g_char->shift++;
		if (g_char->shift == 8)
		{
			ft_printf("B=%i\tS=%i\nL=%i\n", g_char->byte, g_char->shift, (int)g_char->size);
			message = append_char(message, g_char->byte);
			g_char->byte = 0;
			g_char->shift = 0;
		}
		if (ft_strlen(message) == g_char->size)
		{
			ft_putstr_fd(message, 1);
			free(message);
			message = NULL;
		}
	}
}

/*	[TODO]:
 *		-	Receve signal from client.
 *		-	Store the process ID of the sender.
 *		-	Take the signal and send it to a function.
 *		-	This function will build a byte that can be displayed
 *			as its Uni-Code Character Representation.
*/ 
static void	receive_signal(int bit)
{
	//g_Character.client_pid = 123;
	if (bit == SIGUSR1)
		bit = 1;
	else if (bit == SIGUSR2)
		bit = 0;
	build_bytes(bit, &g_Character);
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
	g_Character.byte = 0;
	g_Character.shift = 0;
	ft_printf("Server PID: %u\n", getpid());
	while (1)
	{
		signal(SIGUSR1, receive_signal);
		signal(SIGUSR2, receive_signal);
		pause();
	}
	return (0);
}
