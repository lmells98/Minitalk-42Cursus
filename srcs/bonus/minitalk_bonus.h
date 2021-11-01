#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

#include "../ft_printf/includes/ft_printf.h"
#include <signal.h>

typedef struct s_Character
{
	char			byte;
	int				shift;
	unsigned int	size;
	size_t			client_pid;
}			t_Character;

char	*g_client;


#endif
