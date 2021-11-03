/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:45:14 by lmells            #+#    #+#             */
/*   Updated: 2021/11/03 13:06:06 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/* 	[TODO]:
 *  	-	Take in the value assigned when a SIGUSR signal
 *  		is received.
 *  	-	Store it in a bit array.
 *  	-	Convert bit array to decimal
 *  	-	Display char decimal to screen
*/
static char	*ft_build_bits(char *byte, int c)
{
	char			*bit_arr;
	unsigned int	i;
	unsigned int	size;

	if (!byte)
		byte = ft_strdup("");
	size = ft_strlen(byte);
	bit_arr = (char *)malloc((size + 2) * sizeof(char));
	if (!bit_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		bit_arr[i] = byte[i];
		i++;
	}
	free(byte);
	bit_arr[i] = (char)c;
	bit_arr[i + 1] = '\0';
	return (bit_arr);
}

static void	ft_convert_bits(char *bit_arr, size_t size)
{
	unsigned int	byte;
	unsigned int	i;
	size_t			power;

	if (!bit_arr || size != 8)
	{
		ft_printf("Something went wrong!\n");
		return ;
	}
	byte = 0;
	i = 0;
	power = 1;
	while (size-- > 1)
		power *= 2;
	while (power != 0)
	{
		byte += (bit_arr[i] - '0') * power;
		power /= 2;
		i++;
	}
	ft_putchar_fd(byte, 1);
}

static void	ft_receive_bits(int sig)
{
	static int		count;
	static char		*byte;

	if (byte == NULL)
		count = 0;
	count += 1;
	if (sig == SIGUSR1)
		byte = ft_build_bits(byte, '1');
	else if (sig == SIGUSR2)
		byte = ft_build_bits(byte, '0');
	if (count == 8)
	{
		ft_convert_bits(byte, ft_strlen(byte));
		free(byte);
		byte = NULL;
	}
}

int	main(void)
{
	ft_printf("Server PID %u\n", getpid());
	ft_printf("Run Client in another window to talk...\n");
	ft_printf("Use: ./client <pid> \"message\"\n");
	while (1)
	{
		signal(SIGUSR1, ft_receive_bits);
		signal(SIGUSR2, ft_receive_bits);
		pause();
	}
	return (0);
}
