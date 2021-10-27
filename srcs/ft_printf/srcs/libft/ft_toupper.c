#include "libft.h"

int	ft_toupper(int c)
{
	unsigned char	ch;

	ch = c;
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	return (ch);
}
