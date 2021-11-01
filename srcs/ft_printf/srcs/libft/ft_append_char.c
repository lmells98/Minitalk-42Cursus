#include "./libft.h"

char	*ft_append_char(char *old_arr, char byte)
{
	unsigned int	i;
	char			*new_arr;

	new_arr = (char *)malloc((ft_strlen(old_arr) + 2) * sizeof(char));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (old_arr && old_arr[i] != '\0')
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	new_arr[i] = (unsigned int)byte;
	new_arr[i + 1] = '\0';
	free(old_arr);
	return (new_arr);
}
