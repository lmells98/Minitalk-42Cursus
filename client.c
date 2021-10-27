#include "minitalk.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s && *s++ != '\0')
		len++;
	return (len);
}

static int	send_bits(int s_pid, char *bit_arr, size_t size)
{
	int	ret;
	int	bit;
	int	err;

	ret = 0;
	bit = 0;
	if (bit_arr && s_pid)
	{
		printf("----------\n");
		while (size-- > 0)
		{
			bit = bit_arr[size] - '0';
			if (bit == 1)
				err = kill(s_pid, SIGUSR1);
			else
				err = kill(s_pid, SIGUSR2);
			if (err == 0)
				printf("Bit Sent...\n");
			ret += 1;
			usleep(100);
		}
		return (ret);
	}
	return (ret);
}

static int send_byte(int s_pid, int c, size_t size)
{
	int				ret;
	char 			*bit_arr;
	unsigned int	bit;
	unsigned int	shift;

	//	**Set Binary Array**
	ret = 0;
	bit_arr = (char *)malloc(((size * 8) + 1) * sizeof(char));
	if (!bit_arr)
	{
		printf("ERROR!!! Malloc Failed...\n");
		return (ret);
	}

	//	Shifts Bits down and stores LSB into an array.
	shift = 0;
	while (shift < (size * 8))
	{
		printf("----------\nSetting Bit Array\n");
		printf("shift = %d  <  size = %ld\n", shift, (size * 8));
		
		// Assigns bit value of 1 if 1 bit is found by shift multiplier.
		// Otherwise assigned value of 0.
		// 2 to power of (n - 1).
		bit = (c >> shift) & 1;
		bit_arr[shift] = bit + '0';
		printf("Bit = [%c]\n", bit_arr[shift]);
		shift++;
	}
	bit_arr[shift] = '\0';

	//	Dump Binary Array.
	printf("----------\n");
	for (unsigned int j = 0; j < (size * 8); j++)
		write(1, &bit_arr[j], 1);
	write(1, "\n", 1);

	//	Send Bits to Server, return successful bits sent.
	ret += send_bits(s_pid, bit_arr, ft_strlen(bit_arr));
	free(bit_arr);
	return (ret);
}

static int	get_character_UNI(int s_pid, char *str, size_t size)
{
	printf("----------\nString Info:\n");
	printf("String\t= \'%s\'\nLength\t= %ld\n----------\n", str, ft_strlen(str));
	int				bits;
	char			c;
	unsigned int	i;
	int				c_len;

	i = 0;
	bits = 0;
	c_len = 0;
	while (i < size)
	{
		printf("----------\nGetting char - [%i]\n", (i + 1));
		c = str[i];
		c_len = sizeof(c);
		if (c_len)
		{
			printf("Got Char - \'%c\'\n", c);
			printf("Bytes = %i\n", c_len);
			bits += send_byte(s_pid, c, c_len);
		}
		else
		{
			printf("ERROR!!! Couldnt get size of char from string...\n");
			return (i);
		}
		i++;
	}
	printf("Bits Sent = %i\n", bits);
	return (i);
}

static int	arg_handle(int argc, int s_pid)
{
	if (s_pid)
		printf("Please Enter Server PID correctly...\n");
	if (argc != 3)
	{
		printf("Please Enter Correct Number of Arguments. (3)\n");
		printf("Use: name <pid> \"message\"\n");
		return (0);
	}
	return (1);
}

static int	ft_atoi(const char *s)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	if ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		ret *= 10;
		ret += *s - '0';
		s++;
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	int		bytes;
	int		s_pid;

	bytes = 0;
	s_pid = ft_atoi(argv[1]);
	printf("PID = %d\n", s_pid);
	if (arg_handle(argc, s_pid))
	{
		bytes += get_character_UNI(s_pid, argv[2], ft_strlen(argv[2]));
		printf("Bytes Sent = %i\n", bytes);
	}
	else
		printf("Something Went Wrong...");
	return (0);
}
