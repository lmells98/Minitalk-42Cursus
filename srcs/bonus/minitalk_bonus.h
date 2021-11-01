#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

#include "../ft_printf/includes/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_Character
{
	char			byte;
	int				shift;
	size_t			size;
	unsigned int	client_pid;
}			t_Character;

t_Character	g_Character;

#endif
