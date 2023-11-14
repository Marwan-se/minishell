/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/13 19:30:21 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_update1(t_listock *ls, char *name, char *value, t_gc **ad)
{
	ls->tmpp = *(ls->lst);
	while (ls->tmpp)
	{
		if (checck_syntax(name))
		{
			ls->sts->exit_status = 1;
			printf_and_free(name, value);
			break ;
		}
		else
		{
			ls->sts->exit_status = 0;
			if (!ft_strcmp(ls->tmpp->name, name))
			{
				ls->tmpp->value = ft_strdup1(value, ad);
				break ;
			}
			ls->tmpp = ls->tmpp->next;
		}
	}
	if (!ls->tmpp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, value, ad));
}

void	e_u2(char *name, t_list *tmp, char *value, t_gc **ad)
{
	if (!tmp->value)
		tmp->value = value;
	else
		tmp->value = ft_strjoin1(tmp->value, value, ad);
	(void)name;
}

void	env_update2(t_listock *ls, char *name, char *value, t_gc **ad)
{
	ls->tmpp = *(ls->lst);
	while (ls->tmpp)
	{
		if (checck_syntax(name))
		{
			ls->sts->exit_status = 1;
			printf_and_free(name, value);
			break ;
		}
		else
		{
			ls->sts->exit_status = 0;
			if (!ft_strcmp(ls->tmpp->name, name))
			{
				e_u2(name, ls->tmpp, value, ad);
				break ;
			}
			ls->tmpp = ls->tmpp->next;
		}
	}
	if (!ls->tmpp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, value, ad));
}

void	env_update3(t_listock *ls, char *name, t_gc **ad)
{
	ls->tmpp = *(ls->lst);
	while (ls->tmpp)
	{
		if (checck_syntax(name))
		{
			ls->sts->exit_status = 1;
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			break ;
		}
		else
		{
			ls->sts->exit_status = 0;
			if (!ft_strcmp(ls->tmpp->name, name))
				break ;
			ls->tmpp = ls->tmpp->next;
		}
	}
	if (!ls->tmpp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, NULL, ad));
}

void	case1(t_listock *ls, int j, char *str, t_gc **ad)
{
	char	*name;
	char	*value;

	name = ft_strndup(str, j, ad);
	value = ft_strdup1(str + j + 1, ad);
	env_update1(ls, name, value, ad);
}
