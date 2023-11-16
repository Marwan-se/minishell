/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:25:04 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:16:35 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_echo(char **str, t_parse *ls, t_listock *lss)
{
	ft_echo(str, &ls, lss->sts);
}

void	handle_export(char **str, t_listock *lss, t_parse *ls, t_gc **ad)
{
	if (env_updates(str, lss, ad) == 2 && ls->data[1] == NULL)
		export1(lss->exp, *(lss->lst), &ls, ad);
}

void	handle_cd(char **str, char *pwd, t_listock *lss, t_gc **ad)
{
	ft_cd(pwd, str, lss, ad);
}

void	handle_pwd(t_listock *lss, t_parse *ls, t_gc **ad)
{
	char	*pwd;

	pwd = ft_getenv(*(lss->lst), "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			ft_putstr_fd("", 2);
		ft_lstadd_back22(ad, ft_lstnew22(pwd));
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
