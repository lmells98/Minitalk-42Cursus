/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:47:38 by lmells            #+#    #+#             */
/*   Updated: 2021/11/02 08:47:38 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_percent(char *type)
{
	int	ret;

	ret = 0;
	if (*type == '%')
		ret += print_char(*type);
	return (ret);
}

int	print_sign(char *type)
{
	int	ret;

	ret = 0;
	if (*type == 'p')
		ret += print_str("0x");
	return (ret);
}
