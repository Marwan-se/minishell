/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:25 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 14:19:22 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	update_pwd_cd(t_list *lst, char *NEW_PWD)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			tmp->value = NULL;
			tmp->value = ft_strdup1(NEW_PWD);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back1(&lst, ft_lstnew1("PWD", ft_strdup1(NEW_PWD)));
}

void	update_oldpwd_cd(t_list *lst, char *currentDir)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
		{
			tmp->value = NULL;
			tmp->value = ft_strdup1(currentDir);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back1(&lst, ft_lstnew1("OLDPWD", ft_strdup1(currentDir)));
}

int	cd_auxiliaire(char **av, t_stock *sts)
{
	int	flag;

	if (*(av + 1) && !ft_strcmp(*(av + 1), "~"))
	{
		sts->exit_status = 0;
		if (chdir(getenv("HOME")) == -1)
			(cd_error("HOME", sts));
		flag = 2;
	}
	else if (*(av + 1) && !ft_strcmp(*(av + 1), ".."))
	{
		sts->exit_status = 0;
		if (chdir("..") == -1)
			(cd_error("..", sts));
		flag = 3;
	}
	else
	{
		sts->exit_status = 0;
		if (chdir(*(av + 1)) == -1)
			(cd_error(*(av + 1), sts));
		flag = 4;
	}
	return (flag);
}

void	perrorat(void)
{
	perror ("cd");
	perror ("getcwd");
	perror ("directories");
}

void	cd_home(t_stock *sts)
{
	sts->exit_status = 0;
	if (chdir(getenv("HOME")) == -1)
		(cd_error("HOME", sts));
}
