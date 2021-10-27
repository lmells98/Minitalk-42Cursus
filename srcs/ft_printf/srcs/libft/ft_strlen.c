#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str && *str++ != '\0')
		len++;
	return (len);
}
