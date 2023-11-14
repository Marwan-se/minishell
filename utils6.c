/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:20:13 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:55:08 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc **ad)
{
	char			*sub;
	unsigned int	to_start;
	size_t			newlen;

	if (!s)
		return (NULL);
	to_start = ft_strnlen(s, start);
	newlen = ft_strnlen(s + to_start, len);
	sub = malloc(newlen + 1);
	if (!sub)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(sub));
	if (sub != NULL)
		ft_strlcpy(sub, s + to_start, newlen + 1);
	return (sub);
}

t_parse	*ft_lstnew(char **content, int in, int out, t_gc **ad)
{
	t_parse	*head;

	head = NULL;
	head = malloc(sizeof(t_parse));
	if (!head)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(head));
	head->input = in;
	head->output = out;
	head->data = content;
	head->next = NULL;
	return (head);
}

t_parse	*ft_lstlast(t_parse *lst)
{
	t_parse	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	return (tmp);
}

void	ft_lstadd_back(t_parse **lst, t_parse *new)
{
	t_parse	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last -> next = new;
}
