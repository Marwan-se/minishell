/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:27:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:43 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_file_lim(int *fd, t_cmd **lst, t_listock *ls, t_gc **ad)
{
	if (fd[0] != 0)
		close(fd[0]);
	fd[0] = heredoca((*lst)->data, ls, ad);
	if (fd[0] == -1)
		perror("Erreur lors de l'ouverture du fichier en lecture (lim)");
}

void	fd_fct(int *fd, t_cmd **lst, t_listock *ls, t_gc **ad)
{
	if ((*lst)->type == file_in)
		open_file_in(fd, lst, &(ls->flagg));
	else if ((*lst)->type == file_out)
		open_file_out(fd, lst);
	else if ((*lst)->type == file_append)
		open_file_append(fd, lst);
	else if ((*lst)->type == lim)
		open_file_lim(fd, lst, ls, ad);
}

void	parse_aux(int *fd, t_cmd *tmp, t_listock *ls, t_gc **ad)
{
	while (tmp && tmp->type != pip)
	{
		if (tmp->type == word || tmp->type == sgl_quotes \
		|| tmp->type == dbl_quotes)
		{
			if (tmp)
				tmp = tmp->next;
			(ls->len)++;
		}
		else
		{
			if (!(ls->flagg))
				fd_fct(fd, &tmp, ls, ad);
			if (tmp)
			{
				tmp = tmp->next;
				if (tmp && tmp->type == pip && (ls->flagg))
					ls->flagg = 0;
			}
		}
	}
}

char	**parse_aux2(int len, t_cmd **tmp, t_gc **ad)
{
	int		i;
	char	**data;

	i = 0;
	data = malloc(sizeof(char *) * (len + 1));
	if (!data)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(data));
	while (*tmp && (*tmp)->type != pip)
	{
		if ((*tmp)->type == dbl_quotes || (*tmp)->type == sgl_quotes \
		|| (*tmp)->type == word)
		{
			data[i] = ft_strdup1((*tmp)->data, ad);
			if (*tmp)
				(*tmp) = (*tmp)->next;
			i++;
		}
		else
			if (*tmp)
				(*tmp) = (*tmp)->next;
	}
	data[i] = NULL;
	return (data);
}

t_parse	*parse(t_cmd *lst, t_listock *ls, t_gc **ad)
{
	t_cmd	*tmp;
	t_cmd	*tmpp;
	int		fd[2];
	t_parse	*list;

	ls->flagg = 0;
	list = NULL;
	tmp = lst;
	tmpp = lst;
	while (tmp)
	{
		ls->len = 0;
		fd[0] = 0;
		fd[1] = 1;
		parse_aux(fd, tmp, ls, ad);
		tmp = tmpp;
		ft_lstadd_back(&list, \
		ft_lstnew(parse_aux2(ls->len, &tmp, ad), fd[0], fd[1], ad));
		if (tmp)
			tmp = tmp->next;
		tmpp = tmp;
	}
	return (list);
}
