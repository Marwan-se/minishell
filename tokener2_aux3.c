/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2_aux3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:34:51 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:48 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	list_join_word(t_cmd **lst, t_gc **ad)
{
	t_cmd	*tempr;

	tempr = *lst;
	while ((*lst))
	{
		while ((*lst) && ((*lst)->type == word || \
			(*lst)->type == dbl_quotes || (*lst)->type == sgl_quotes))
		{
			join_words(lst, ad);
		}
		if ((*lst))
			(*lst) = (*lst)->next;
	}
	*lst = tempr;
}

void	list_del_spaces(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*tempr;

	if (lst == NULL || *lst == NULL)
		return ;
	tempr = *lst;
	while (*lst)
	{
		if ((*lst)->type == spaces)
		{
			temp = *lst;
			deletenode(lst, temp);
		}
		if (*lst)
			*lst = (*lst)->next;
	}
	*lst = tempr;
}

void	list_rd_herdc(t_cmd	*lst)
{
	while (lst)
	{
		if (lst->type == rd_input && lst->next)
			lst->next->type = file_in;
		else if (lst->type == rd_output && lst->next)
			lst->next->type = file_out;
		else if (lst->type == rd_append && lst->next)
			lst->next->type = file_append;
		else if (lst->type == heredoc && lst->next)
			lst->next->type = lim;
		lst = lst->next;
	}
}

void	list_del_rd(t_cmd **lst)
{
	t_cmd	*tmp;
	t_cmd	*tmpr;

	if (lst == NULL || *lst == NULL)
		return ;
	tmpr = *lst;
	while (*lst)
	{
		if ((*lst)->type == rd_input || (*lst)->type == rd_append || \
			(*lst)->type == rd_output || (*lst)->type == heredoc)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			deletenode(&tmpr, tmp);
		}
		else
			*lst = (*lst)->next;
	}
	*lst = tmpr;
}

void	join_rd_del(t_cmd **lst, t_gc **ad)
{
	list_join_word(lst, ad);
	list_del_spaces(lst);
	list_rd_herdc(*lst);
	list_del_rd(lst);
}
