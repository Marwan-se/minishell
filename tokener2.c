/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:57:03 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:50 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	lexer(char	*str)
{
	t_cmd	tp;

	if (str && str[0] && (str[0] == ' ' || str[0] == '\t'))
		tp.type = spaces;
	else if (str && str[0] && str[0] == '|')
		tp.type = pip;
	else if (str && !ft_strcmp(str, ">"))
		tp.type = rd_output;
	else if (str && !ft_strcmp(str, "<"))
		tp.type = rd_input;
	else if (str && !ft_strcmp(str, "<<"))
		tp.type = heredoc;
	else if (str && !ft_strcmp(str, ">>"))
		tp.type = rd_append;
	else if (str && str[0] && str[0] != ' ' && \
	str[0] != '\t' && str[0] != '<' && \
	str[0] != '>' && str[0] != '|' && str[0] != '\'' && str[0] != '"')
		tp.type = word;
	return (tp.type);
}

t_cmd	*list(char **str, t_cmd	**lst, t_gc **ad)
{
	int	i;

	i = 0;
	while (str[i])
	{
		(*lst) = add_back(*lst, str[i], ad);
		i++;
	}
	return (*lst);
}

char	*ft_strjoin(char *s1, char *s2, t_gc **ad)
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

void	deletenode(t_cmd **head, t_cmd *lst)
{
	if (*head == NULL || lst == NULL)
		return ;
	if (*head == lst)
		*head = lst->next;
	if (lst->next != NULL)
		lst->next->previous = lst->previous;
	if (lst->previous != NULL)
		lst->previous->next = lst->next;
}

void	join_words(t_cmd **lst, t_gc **ad)
{
	char	*new_data;
	t_cmd	*temp;

	if ((*lst)->next && (
			(*lst)->next->type == word || \
			(*lst)->next->type == dbl_quotes || \
			(*lst)->next->type == sgl_quotes))
	{
		new_data = ft_strjoin((*lst)->data, (*lst)->next->data, ad);
		(*lst)->data = new_data;
		temp = (*lst)->next;
		deletenode(lst, temp);
	}
	else
		(*lst) = (*lst)->next;
}
