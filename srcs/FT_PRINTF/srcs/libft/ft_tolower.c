#include "libft.h"

int	ft_tolower(int c)
{
	unsigned char	ch;

	ch = c;
	if (ch >= 'A' && ch <= 'Z')
		ch += 32;
	return (ch);
}
