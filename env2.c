/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:07 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:52:32 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_list(t_list **lst, char **environnement, t_gc **ad)
{
	int		i;
	char	**dst;

	i = 0;
	*lst = NULL;
	while (environnement[i])
	{
		dst = split_souad(environnement[i], ad);
		ft_lstadd_back1(lst, ft_lstnew1(dst[0], dst[1], ad));
		i++;
	}
	the_pwd_print(lst, ad);
	shlvl_increment(lst, ad);
	the_eight_dash(lst, ad);
	the_oldpwd_print(lst, ad);
}

void	env(int ac, char **av, t_list **lst, t_parse	**ls)
{
	t_list	*tmp;

	(void)ac;
	(void)av;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->name && tmp->value)
		{
			ft_putstr_fd(tmp->name, (*ls)->output);
			ft_putstr_fd("=", (*ls)->output);
			ft_putstr_fd(tmp->value, (*ls)->output);
			ft_putstr_fd("\n", (*ls)->output);
		}
		tmp = tmp->next;
	}
}
