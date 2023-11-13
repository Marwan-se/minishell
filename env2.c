/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:07 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 11:59:08 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_list(t_list **lst, char **environnement)
{
	int		i;
	char	**dst;

	i = 0;
	*lst = NULL;
	while (environnement[i])
	{
		dst = split_souad(environnement[i]);
		ft_lstadd_back1(lst, ft_lstnew1(dst[0], dst[1]));
		i++;
	}
	the_pwd_print(lst);
	shlvl_increment(lst);
	the_eight_dash(lst);
	the_oldpwd_print(lst);
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
