/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:18 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:38 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_export(char *str, int j, t_listock *ls, t_gc **ad)
{
	if (j && str[j] == '=' && str[j - 1] != '+')
		case1(ls, j, str, ad);
	else
		case2(ls, j, str, ad);
}

int	env_updates(char **av, t_listock *ls, t_gc **ad)
{
	int			j;
	char		*str;
	char		**s;

	if (*av && !ft_strcmp(*av, "export"))
	{
		s = av + 1;
		while (*s)
		{
			str = *s;
			j = 0;
			while (*s && str[j] && str[j] != '=')
				j++;
			env_export(str, j, ls, ad);
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

t_exp	*export(t_list **lst, t_gc **ad)
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
			tmp4 = ft_strjoin1("declare -x ", (*lst)->name, ad);
		else
		{
			tmp = ft_strjoin1((*lst)->name, "=\"", ad);
			tmp2 = ft_strjoin1(tmp, (*lst)->value, ad);
			tmp3 = ft_strjoin1(tmp2, "\"", ad);
			tmp4 = ft_strjoin1("declare -x ", tmp3, ad);
		}
		ft_lstadd_back2(&list, ft_lstnew2(tmp4, ad));
		(*lst) = (*lst)->next;
	}
	return (list);
}

void	export1(t_exp *list, t_list *lst, t_parse **ls, t_gc **ad)
{
	list = export(&lst, ad);
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
