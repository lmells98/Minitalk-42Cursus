#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			elem = ft_lstlast(*lst);
			if (elem)
				elem->next = new;
		}
	}
}
