/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:04:39 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:41 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_gc	*ft_lstnew22(void *content)
{
	t_gc	*head;

	head = NULL;
	head = malloc(sizeof(t_gc));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

t_gc	*ft_lstlast22(t_gc *lst)
{
	t_gc	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!(tmp->next))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstadd_back22(t_gc **lst, t_gc *new)
{
	t_gc	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast22(*lst);
	last -> next = new;
}

void	ft_lstclear(t_gc **lst)
{
	t_gc	*temp;
	t_gc	*t;

	if (!*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		t = temp->next;
		free(temp->content);
		free(temp);
		temp = t;
	}
	*lst = NULL;
}
