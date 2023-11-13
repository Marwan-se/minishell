/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:25:04 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:26:39 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_echo(char **str, t_parse *ls, t_listock *lss)
{
	ft_echo(str, &ls, lss->sts);
}

void	handle_export(char **str, t_exp **exp, t_listock *lss, t_parse *ls)
{
	if (env_updates(str, lss) == 2 && ls->data[1] == NULL)
		export1(*exp, *(lss->lst), &ls);
}

void	handle_cd(char **str, t_list **lst, char *pwd, t_listock *lss)
{
	ft_cd(*lst, pwd, str, lss->sts);
}

void	handle_pwd(t_listock *lss, t_parse *ls)
{
	char	*pwd;

	pwd = ft_getenv(*(lss->lst), "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_putstr_fd("", 2);
		ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(pwd));
	}
	pwdd(pwd, &ls);
	lss->sts->exit_status = 0;
}

void	handle_env(char **str, t_parse *ls, t_listock *lss)
{
	if (str[0] && !str[1])
	{
		env(0, str, lss->lst, &ls);
		lss->sts->exit_status = 0;
	}
	else if (str[0] && str[1])
	{
		env_error(str);
		lss->sts->exit_status = 127;
	}
}
