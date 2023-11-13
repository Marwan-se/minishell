/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:18:58 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:54:40 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	cd_aux(char **av, t_stock *sts, int *flag)
{
	if (*av && !ft_strcmp(*av, "cd") && !*(av + 1))
	{
		cd_home(sts);
		*flag = 1;
	}
	else if (*av && !ft_strcmp(*av, "cd") && *(av + 1))
		*flag = cd_auxiliaire(av, sts);
}

void	cd_aux2(char *c, char **n)
{
	*n = ft_strjoin(c, "/..");
	perrorat();
}

void	ft_cd(t_list *lst, char *pwd, char **av, t_stock *sts)
{
	char	newpwd[PATH_MAX];
	char	currentdir[PATH_MAX];
	char	*n;
	char	*c;
	int		flag;

	(void)pwd;
	flag = 0;
	n = newpwd;
	c = ft_getenv(lst, "PWD");
	if (!c)
	{
		c = getcwd(NULL, 0);
		ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(c));
	}
	getcwd(currentdir, PATH_MAX);
	cd_aux(av, sts, &flag);
	if (!getcwd(newpwd, PATH_MAX))
		cd_aux2(c, &n);
	if (flag)
		(update_pwd_cd(lst, n), update_oldpwd_cd(lst, c));
}
