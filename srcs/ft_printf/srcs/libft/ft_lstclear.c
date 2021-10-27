#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*free_elem;

	if (!lst)
		return ;
	elem = *lst;
	while (elem)
	{
		free_elem = elem;
		elem = elem->next;
		ft_lstdelone(free_elem, del);
	}
	*lst = NULL;
}
