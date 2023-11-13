/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:18 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 11:58:19 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_export(char *str, int j, t_list	*tmp, t_listock *ls)
{
	if (j && str[j] == '=' && str[j - 1] != '+')
		case1(tmp, ls, j, str);
	else
		case2(tmp, ls, j, str);
}

int	env_updates(char **av, t_listock *ls)
{
	int			j;
	char		*str;
	char		**s;
	t_list		*tmp;

	tmp = NULL;
	if (*av && !ft_strcmp(*av, "export"))
	{
		s = av + 1;
		while (*s)
		{
			str = *s;
			j = 0;
			while (*s && str[j] && str[j] != '=')
				j++;
			env_export(str, j, tmp, ls);
			s++;
		}
	}
	s = av;
	if ((*s && !ft_strcmp(*s, "export") && !*(s + 1)) || \
	(*s && !ft_strcmp(*s, "export") && *(s + 1)))
		return (2);
	return (0);
}

void	trier(t_exp *lst)
{
	char	*swap;
	t_exp	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if ((ft_strcmp(lst->content, lst->next->content) > 0))
		{
			swap = lst->content;
			lst->content = lst->next->content;
			lst->next->content = swap;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
}

t_exp	*export(t_list **lst)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	t_exp	*list;

	list = NULL;
	while (lst && *lst)
	{
		if ((*lst)->value == NULL)
			tmp4 = ft_strjoin1("declare -x ", (*lst)->name);
		else
		{
			tmp = ft_strjoin1((*lst)->name, "=\"");
			tmp2 = ft_strjoin1(tmp, (*lst)->value);
			tmp3 = ft_strjoin1(tmp2, "\"");
			tmp4 = ft_strjoin1("declare -x ", tmp3);
		}
		ft_lstadd_back2(&list, ft_lstnew2(tmp4));
		(*lst) = (*lst)->next;
	}
	return (list);
}

void	export1(t_exp *list, t_list *lst, t_parse **ls)
{
	list = export(&lst);
	if (!list)
		return ;
	trier(list);
	while (list)
	{
		ft_putstr_fd(list->content, (*ls)->output);
		ft_putstr_fd("\n", (*ls)->output);
		list = list->next;
	}
}
