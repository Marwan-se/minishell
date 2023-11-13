/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 22:09:51 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	env_update1(t_list *tmp, t_listock *ls, char *name, char *value)
{
	tmp = *(ls->lst);
	while (tmp)
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
			if (!ft_strcmp(tmp->name, name))
			{
				//free(name);
				//free(tmp->value);
				tmp->value = ft_strdup1(value);
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (!tmp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, value));
}

void	e_u2(char *name, t_list *tmp, char *value)
{
	//free(name);
	if (!tmp->value)
		tmp->value = value;
	else
		tmp->value = ft_strjoin1(tmp->value, value);
	(void)name;
}

void	env_update2(t_list *tmp, t_listock *ls, char *name, char *value)
{
	tmp = *(ls->lst);
	while (tmp)
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
			if (!ft_strcmp(tmp->name, name))
			{
				e_u2(name, tmp, value);
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (!tmp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, value));
}

void	env_update3(t_list *tmp, t_listock *ls, char *name)
{
	tmp = *(ls->lst);
	while (tmp)
	{
		if (checck_syntax(name))
		{
			ls->sts->exit_status = 1;
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			//free(name);
			break ;
		}
		else
		{
			ls->sts->exit_status = 0;
			if (!ft_strcmp(tmp->name, name))
			{
				//free(name);
				break ;
			}
			tmp = tmp->next;
		}
	}
	if (!tmp)
		ft_lstadd_back1(ls->lst, ft_lstnew1(name, NULL));
}

void	case1(t_list *tmp, t_listock *ls, int j, char *str)
{
	char	*name;
	char	*value;

	name = ft_strndup(str, j);
	value = ft_strdup1(str + j + 1);
	env_update1(tmp, ls, name, value);
}
