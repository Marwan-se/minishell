/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:27 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:28 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen1(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_exp	*ft_lstnew2(char *content, t_gc **ad)
{
	t_exp	*head;

	head = NULL;
	head = malloc(sizeof(t_exp));
	if (!head)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(head));
	head->content = content;
	head->next = NULL;
	return (head);
}

t_exp	*ft_lstlast2(t_exp *lst)
{
	t_exp	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	return (tmp);
}

void	ft_lstadd_back2(t_exp **lst, t_exp *new)
{
	t_exp	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast2(*lst);
	last -> next = new;
}

char	*ft_strjoin1(char *s1, char *s2, t_gc **ad)
{
	int		i;
	char	*src;

	if (s1 && s2)
	{
		src = malloc(sizeof(char) * (ft_strlen1(s1) + ft_strlen1(s2) + 1));
		if (!src)
			exit (1);
		ft_lstadd_back22(ad, ft_lstnew22(src));
		i = -1;
		while (s1[++i])
			src[i] = s1[i];
		i = -1;
		while (s2[++i])
			src[ft_strlen1(s1) + i] = s2[i];
		src[ft_strlen1(s1) + i] = '\0';
		return (src);
	}
	return (NULL);
}
