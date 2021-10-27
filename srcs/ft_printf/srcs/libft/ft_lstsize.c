#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	len;
	t_list	*elems;

	elems = lst;
	len = 0;
	while (elems)
	{
		elems = elems->next;
		len++;
	}
	return (len);
}
