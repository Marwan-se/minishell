/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:45 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:22 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define MAX_ENV_VAR_SIZE 4096
#define MAX_ENV_NAME_SIZE 100

char	*ft_getenv(t_list *lst, const char	*variable_name)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, variable_name))
			break ;
		tmp = tmp->next;
	}
	if (tmp && !(tmp->value))
		return (NULL);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

void	fill_stack_var(t_variables	*var, char **inpute, char	*variable_name)
{
	char		*input;

	var->i = 0;
	input = *inpute;
	var->k = *input;
	if (!ft_isdigit(var->k) && var->k != '*')
	{
		while (*input != '\0' && (ft_isdigit(*(input)) || \
		ft_isalpha(*(input)) || \
		*(input) == '_') && var->i < (MAX_ENV_NAME_SIZE - 1))
			variable_name[var->i++] = *(input++);
	}
	else
		input++;
	variable_name[var->i] = '\0';
	*inpute = input;
}

void	update_result(char **res_ptr, char *value)
{
	ft_strcpy(*res_ptr, value);
	*res_ptr += ft_strlen1(value);
}

void	handle_variable(char *variable_name, \
t_listock *ls, char **res_ptr, t_gc **ad)
{
	char	k;
	char	*value;

	k = (*(ls->input))[0];
	if (k != '?')
	{
		value = ft_getenv(*(ls->lst), variable_name);
		if (value)
			update_result(res_ptr, value);
	}
	else
	{
		value = ft_itoa(ls->sts->exit_status, ad);
		if (value)
		{
			update_result(res_ptr, value);
			(*(ls->input))++;
		}
	}
}

void	handle_flags(char **input, int *flag)
{
	if ((*input)[0] == '\'' && *flag == 0)
		*flag = 1;
	else if ((*input)[0] == '\'' && *flag == 1)
		*flag = 0;
	if ((*input)[0] == '"' && *flag == 0)
		*flag = 2;
	else if ((*input)[0] == '"' && *flag == 2)
		*flag = 0;
}
