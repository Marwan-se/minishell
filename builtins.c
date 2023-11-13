/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:50:41 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:27:24 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	builtin(t_parse *ls, t_exp **exp, t_listock *lss)
{
	char	**str;

	str = ls->data;
	if (!str || !str[0])
		return (0);
	if (echo_combinaison(str[0]))
		handle_echo(str, ls, lss);
	else if (!ft_strcmp(str[0], "export") && !str[1])
		handle_export(str, exp, lss, ls);
	else if (!ft_strcmp(str[0], "cd"))
		handle_cd(str, lss->lst, NULL, lss);
	else if (pwd_combinaison(str[0]))
		handle_pwd(lss, ls);
	else if (env_combinaison(str[0]))
		handle_env(str, ls, lss);
	else
		return (0);
	return (1);
}

void	handle_export2(char **str, t_listock *lss, t_parse *ls)
{
	if (!env_updates(str, lss) && ls->data[1])
		;
}

void	handle_unset2(char **str, t_listock *lss)
{
	if (!unset(str, lss->lst, lss->sts))
		;
}

int	builtin2(t_parse *ls, t_listock *lss)
{
	char	**str;
	char	*pwd;

	str = ls->data;
	if (!str || !str[0])
		return (0);
	if (!ft_strcmp(str[0], "export") && str[1])
		handle_export2(str, lss, ls);
	else if (!ft_strcmp(str[0], "unset"))
		handle_unset2(str, lss);
	else if (!ft_strcmp(str[0], "exit"))
		exit1(str, lss->sts);
	else if (!ft_strcmp(str[0], "cd"))
	{
		pwd = getcwd(NULL, 0);
		ft_cd(*(lss->lst), pwd, str, lss->sts);
		ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(pwd));
	}
	else
		return (0);
	return (1);
}

int	ft_lstsize(t_parse *lst)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}
