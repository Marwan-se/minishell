/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:54:30 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:16 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	chk_quote(char *str, int *i, int *flag2, char *quote)
{
	if (*flag2 == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*flag2 = 1;
		*quote = str[*i];
	}
	else if (*flag2 == 1 && str[*i] == *quote)
	{
		*flag2 = 0;
	}
	(*i)++;
	return (*i);
}

int	check_brackets(char *str, int *i)
{
	int	initial_index;

	initial_index = *i;
	while (str[*i] && (str[*i] == '<' || str[*i] == '>'))
		(*i)++;
	if (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
		if (str[*i] && (str[*i] == '<' || str[*i] == '>'))
		{
			*i = initial_index;
			return (1);
		}
	}
	*i = initial_index;
	return (0);
}

int	check_conditions(char *str, int *index, int flag2)
{
	int	i;

	i = *index;
	if (!flag2 && str[i] && str[i] == '<')
	{
		i++;
		if (check_brackets(str, &i))
			return (1);
	}
	else if (!flag2 && str[i] && str[i] == '>')
	{
		i++;
		if (check_brackets(str, &i))
			return (1);
	}
	return (0);
}

int	op_op_space(char *str)
{
	int		i;
	int		flag;
	int		flag2;
	int		len;
	char	quote;

	i = 0;
	flag = 0;
	flag2 = 0;
	len = ft_strlen1(str);
	while (len)
	{
		while (str[i] && str[i] != '>' && str[i] != '<')
			i = chk_quote(str, &i, &flag2, &quote);
		if (check_conditions(str, &i, flag2))
		{
			flag = 1;
			break ;
		}
		if (str[i])
			i++;
		len--;
	}
	return (flag);
}

int	check_syntax(char	*str, t_stock *sts)
{
	if (!check_quotes(str, 0) || \
	pip_after_pip(str) || check_end_op_pipe(str) || \
	check_beg_pip(str) || slash_vgl(str) || op_before_pip(str) || \
	op_op_no_space(str) || op_op_space(str))
		return (sts->exit_status = 258, \
		ft_putstr_fd("erreur syntaxique\n", 2), 1);
	return (0);
}
