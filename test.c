#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

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

static int	send_bits(char *bit_arr, size_t size)
{
	int	ret;

	ret = 0;
	if (bit_arr && size)
	{
		printf("----------\n");
		while (size-- > 0)
		{
			printf("Bit Sent...\n");
			ret += 1;
		}
		return (ret);
	}
	return (ret);
}

static int send_char(int ch_p, size_t size)
{
	int				ret;
	char 			*bit_arr;
	unsigned int	bit;
	unsigned int	shift;

	ret = 0;
	bit_arr = (char *)malloc(((size * 8) + 1) * sizeof(char));
	if (!bit_arr)
	{
		printf("ERROR!!! Malloc Failed...\n");
		return (ret);
	}
	shift = 0;
	while (shift < (size * 8))
	{
		printf("----------\nSetting Bit Array\n");
		printf("shift = %d  -  size = %ld\n", shift, (size * 8));
		bit = (ch_p >> shift) & 1;
		bit_arr[shift] = bit + '0';
		printf("Bit = [%c]\n", bit_arr[shift]);
		shift++;
	}
	bit_arr[shift] = '\0';
	printf("----------\n");
	for (unsigned int j = 0; j < (size * 8); j++)
		write(1, &bit_arr[j], 1);
	write(1, "\n", 1);
	ret += send_bits(bit_arr, ft_strlen(bit_arr));
	free(bit_arr);
	return (ret);
}

static int	get_string(char *str, size_t size)
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
			bits += send_char(c, c_len);
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

static int	arg_handle(int argc)
{
	if (argc != 3)
	{
		printf("Please Enter Correct Number of Arguments. (3)\n");
		printf("Use: name <pid> \"message\"\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		bytes;
	int		pid;

	pid = getpid();
	printf("Please Enter PID Followed by message...\n");
	printf("PID = %d\n", pid);
	bytes = 0;
	if (arg_handle(argc))
	{
		bytes += get_string(argv[2], ft_strlen(argv[2]));
		printf("Bytes Sent = %i\n", bytes);
	}
	else
		printf("Something Went Wrong...");
	return (0);
}
