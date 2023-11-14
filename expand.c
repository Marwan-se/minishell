/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:38 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/13 20:36:45 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define MAX_ENV_VAR_SIZE 4096
#define MAX_ENV_NAME_SIZE 100

int	is_valid(char *input)
{
	if (*input == '$' && (ft_isdigit(*(input + 1)) \
		|| ft_isalpha(*(input + 1)) || \
		*(input + 1) == '_' || *(input + 1) == '?' || *(input + 1) == '*'))
		return (1);
	return (0);
}

int	quote_after_dollar(char *input)
{
	if ((*input == '$') && (*(input + 1) == '\'' \
		|| *(input + 1) == '\"'))
		return (1);
	return (0);
}

void	check_after_heredoc(char	*input, int	*flag, int	*flag_word)
{
	if (*input == '<' && *(input + 1) == ' ')
		return ;
	if (*input == '<' && *(input + 1) == '<' && !(*flag))
		*flag = 1;
	else if (*flag && *flag_word == 0 && (*input != ' ' || *input != '\t'))
		*flag_word = 1;
	else if (*flag && *flag_word && (*input == ' ' || *input == '\t'))
	{
		*flag = 0;
		*flag_word = 0;
	}
}

void	add_for_norm(char **inputee, t_variables *var, t_listock *ls, t_gc **ad)
{
	char	*input;
	char	variable_name[MAX_ENV_NAME_SIZE];

	input = *inputee;
	ls->input = &input;
	if (is_valid(input) && !var->flag_to_heredoc)
	{
		input++ ;
		fill_stack_var(var, &input, variable_name);
		handle_variable(variable_name, ls, &var->res_ptr, ad);
	}
	else if (quote_after_dollar(input) && !var->flag_to_heredoc)
		input++;
	else
	{
		check_after_heredoc(input, &var->flag_to_heredoc, &var->flag_word);
		*var->res_ptr++ = *input++;
	}
	*inputee = input;
}

char	*expand_variables(char *input, t_listock *ls, t_gc **ad)
{
	t_variables	var;

	var.result = malloc(MAX_ENV_VAR_SIZE * 2 + 1);
	if (!var.result)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(var.result));
	var.res_ptr = var.result;
	var.flag = 0;
	var.flag_to_heredoc = 0;
	var.flag_word = 0;
	while (*input)
	{
		handle_flags((char **)&input, &var.flag);
		if (var.flag != 1)
			add_for_norm(&input, &var, ls, ad);
		else
			*var.res_ptr++ = *input++;
	}
	return (*var.res_ptr = '\0', var.result);
}
