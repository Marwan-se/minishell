/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:18:01 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:08:28 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*src;
	char	*dst;

	src = (char *)s;
	dst = ft_calloc(n + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

t_list	*ft_lstnew1(char *name, char *value)
{
	t_list	*head;

	head = NULL;
	head = malloc(sizeof(t_list));
	if (!head)
		exit (1);
	ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(head));
	head->name = name;
	head->value = value;
	head->next = NULL;
	return (head);
}

t_list	*ft_lstlast1(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	return (tmp);
}

void	ft_lstadd_back1(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast1(*lst);
	last -> next = new;
}

int	ft_lstsize1(t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}
