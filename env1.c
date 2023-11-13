/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:12 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:11:56 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**split_souad(char *line_env)
{
	int		i;
	char	**dst;
	char	*name;
	char	*value;

	i = 0;
	dst = (char **)malloc(sizeof(char **) * 3);
	if (!dst)
		exit (1);
	ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(dst));
	while (line_env[i] != '=')
		i++;
	name = ft_strndup(line_env, i);
	value = ft_strdup1(line_env + i + 1);
	dst[0] = name;
	dst[1] = value;
	dst[2] = NULL;
	return (dst);
}

void	shlvl_increment(t_list **lst)
{
	t_list	*tmp;
	int		flag;
	int		a;

	flag = 0;
	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "SHLVL"))
		{
			a = atoi(tmp->value);
			//free(tmp->value);
			a += 1;
			tmp->value = ft_strdup1(ft_itoa(a));
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!flag && !tmp)
		ft_lstadd_back1(lst, ft_lstnew1("SHLVL", "1"));
}

void	the_pwd_print(t_list **lst)
{
	t_list	*tmp;
	char	*pwd;

	pwd = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		pwd = getcwd(NULL, 0);
		ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(pwd));
		if (pwd)
			ft_lstadd_back1(lst, ft_lstnew1("PWD", pwd));
	}
}

void	the_oldpwd_print(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back1(lst, ft_lstnew1("OLDPWD", NULL));
}

void	the_eight_dash(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "_"))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back1(lst, ft_lstnew1("_", "/usr/bin/env"));
}
