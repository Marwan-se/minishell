/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:56:28 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:54 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	set_cmd_data_type(t_cmd *temp, char *data, t_gc **ad)
{
	if (data[0] == '\'')
	{
		temp->data = ft_substr(data, 1, ft_strlen(data) - 2, ad);
		temp->type = sgl_quotes;
	}
	else if (data[0] == '"')
	{
		temp->data = ft_substr(data, 1, ft_strlen(data) - 2, ad);
		temp->type = dbl_quotes;
	}
	else
	{
		temp->data = data;
		temp->type = lexer(data);
	}
}

t_cmd	*add_back(t_cmd *head, char *data, t_gc **ad)
{
	t_cmd	*temp;
	t_cmd	*tp;

	tp = head;
	temp = (t_cmd *)ft_calloc(1, sizeof(t_cmd), ad);
	if (!temp)
		return (NULL);
	temp->next = NULL;
	temp->previous = NULL;
	set_cmd_data_type(temp, data, ad);
	if (!head)
		head = temp;
	else
	{
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = temp;
		temp->previous = tp;
	}
	return (head);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*s;
	size_t	k;

	i = 0;
	s = (char *)src;
	k = ft_strlen(s);
	if (dstsize == 0)
		return (k);
	while (s[i] && i < dstsize - 1)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (k);
}

size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i])
		i++;
	return (i);
}
