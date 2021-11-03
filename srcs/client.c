/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:13 by lmells            #+#    #+#             */
/*   Updated: 2021/11/03 12:42:04 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	ft_send_bits(int s_pid, char *bit_arr, size_t size)
{
	int	ret;
	int	bit;
	int	err;

	ret = 0;
	bit = 0;
	if (bit_arr && s_pid)
	{
		while (size-- > 0)
		{
			bit = bit_arr[size] - '0';
			if (bit == 1)
				err = kill(s_pid, SIGUSR1);
			else
				err = kill(s_pid, SIGUSR2);
			if (err == -1)
				ft_printf("Failed to Send...\n");
			ret += 1;
			usleep(200);
		}
		return (ret);
	}
	ft_printf("Error! Something went wrong...\n");
	return (ret);
}

static int	ft_send_byte(int s_pid, int c, size_t size)
{
	int				ret;
	char			*bit_arr;
	unsigned int	bit;
	unsigned int	shift;

	ret = 0;
	bit_arr = (char *)malloc(((size * 8) + 1) * sizeof(char));
	if (!bit_arr)
	{
		ft_printf("ERROR!!! Malloc Failed...\n");
		return (ret);
	}
	shift = 0;
	while (shift < (size * 8))
	{
		bit = (c >> shift) & 1;
		bit_arr[shift] = bit + '0';
		shift++;
	}
	bit_arr[shift] = '\0';
	ret += ft_send_bits(s_pid, bit_arr, ft_strlen(bit_arr));
	free(bit_arr);
	return (ret);
}

static int	ft_get_character(int s_pid, char *str, size_t size)
{
	int				bits;
	char			c;
	unsigned int	i;
	int				c_len;

	i = 0;
	bits = 0;
	c_len = 0;
	while (i < size)
	{
		c = str[i];
		c_len = sizeof(c);
		if (c_len)
			bits += ft_send_byte(s_pid, c, c_len);
		else
		{
			ft_printf("ERROR!!! Couldnt get size of char from string...\n");
			return (i);
		}
		i++;
	}
	ft_printf("Bits Sent = %i\n", bits);
	return (i);
}

static int	ft_arg_handle(int argc)
{
	if (argc != 3)
	{
		ft_printf("Please Enter Correct Number of Arguments. (3)\n");
		ft_printf("Use: name <pid> \"message\"\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		bytes;
	int		s_pid;

	bytes = 0;
	s_pid = ft_atoi(argv[1]);
	if (ft_arg_handle(argc))
		bytes += ft_get_character(s_pid, argv[2], ft_strlen(argv[2]));
	return (0);
}
