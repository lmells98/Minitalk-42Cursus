/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:59 by lmells            #+#    #+#             */
/*   Updated: 2021/11/03 11:37:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "../ft_printf/includes/ft_printf.h"
# include <signal.h>
# include <sys/types.h>

typedef struct s_character
{
	char			byte;
	int				shift;
	size_t			size;
}			t_character;

#endif
