/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:49 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:11:56 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define MAX_ENV_VAR_SIZE 4096
#define MAX_ENV_NAME_SIZE 100

int	is_valid(char *input);

int	quote_after_dollar(char *input);

void	check_limiter(char	*str, int	*index, t_stock *sts)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		if (str[i] == '\'' || str[i] == '"')
			sts->quote_heredoc = 1;
		i++;
	}
	*index += i + 2;
}

void	flag_heredoc_quote(char	*str, t_stock *sts)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			sts->quote_heredoc = 0;
			check_limiter(&str[i + 2], &i, sts);
		}
		i++;
	}
}

char	*expand_heredoc(char *input, t_listock *ls)
{
	t_variables	var;
	char		variable_name[MAX_ENV_NAME_SIZE];

	var.result = malloc(MAX_ENV_VAR_SIZE * 2 + 1);
	if (!var.result)
		exit (1);
	ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(var.result));
	var.res_ptr = var.result;
	while (*input)
	{
		if (is_valid(input))
		{
			input++ ;
			fill_stack_var(&var, &input, variable_name);
			handle_variable(&input, variable_name, ls, &var.res_ptr);
		}
		else if (quote_after_dollar(input))
			input++;
		else
			*var.res_ptr++ = *input++;
	}
	return (*var.res_ptr = '\0', var.result);
}
