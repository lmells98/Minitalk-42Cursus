#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t	len;
	t_list	*elems;

	if (!lst)
		return (NULL);
	elems = lst;
	len = 0;
	while (elems->next != NULL)
	{
		elems = elems->next;
		len++;
	}
	return (elems);
}
