/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:55:17 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 16:07:18 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_operator(char *str, int index, char operator, int *flag)
{
	if (str[index] && str[index] == operator)
	{
		if (str[index + 1] && (str[index + 1] == ' ' || \
			str[index + 1] == '\t' || str[index + 1] == operator))
		{
			index++;
			while (str[index] && (str[index] == ' ' || \
				str[index] == '\t' || str[index] == operator))
				index++;
			if (str[index] == '\'' || str[index] == '"')
				return (1);
			if (str[index] && str[index] == '|')
			{
				*flag = 1;
				return (1);
			}
		}
		else if (str[index + 1] && str[index + 1] == '|')
		{
			*flag = 1;
			return (1);
		}
	}
	return (0);
}

int	op_before_pip(char *str)
{
	int		i;
	int		len;
	int		flag;
	int		flag2;
	char	quote;

	len = ft_strlen1(str);
	flag = 0;
	flag2 = 0;
	i = 0;
	while (len)
	{
		while (str[i] && (str[i] != '<' && str[i] != '>'))
			is_inside_quotes(str, i++, &flag2, &quote);
		if (!flag2 && str[i] && (str[i] == '<' || str[i] == '>'))
		{
			if (check_operator(str, i, str[i], &flag))
				break ;
		}
		if (str[i])
			i++;
		len--;
	}
	return (flag);
}

int	check_triple_operator(char *str, int i)
{
	if (str[i] && str[i] == '>' && str[i + 1] && \
		str[i + 1] == '>' && str[i + 2] && str[i + 2] == '>')
		return (1);
	else if (str[i] && str[i] == '<' && str[i + 1] && \
		str[i + 1] == '<' && str[i + 2] && str[i + 2] == '<')
		return (1);
	else if (str[i] && str[i] == '>' && str[i + 1] && \
		str[i + 1] == '>' && str[i + 2] && str[i + 2] == '<')
		return (1);
	else if (str[i] && str[i] == '<' && str[i + 1] && \
		str[i + 1] == '<' && str[i + 2] && str[i + 2] == '>')
		return (1);
	else if (str[i] && str[i] == '>' && str[i + 1] && \
		str[i + 1] == '<')
		return (1);
	else if (str[i] && str[i] == '<' && str[i + 1] && \
		str[i + 1] == '>')
		return (1);
	else
		return (0);
}

int	process_string(char *str)
{
	int		i;
	int		flag2;
	char	quote;

	i = 0;
	flag2 = 0;
	while (str[i] && str[i] != '>' && str[i] != '<')
	{
		if (flag2 == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			flag2 = 1;
			quote = str[i];
		}
		else if (flag2 == 1 && str[i] == quote)
			flag2 = 0;
		i++;
	}
	return (i);
}

int	op_op_no_space(char *str)
{
	int		flag;
	int		len;
	int		i;
	int		flag2;

	flag = 0;
	len = ft_strlen1(str);
	i = 0;
	flag2 = 0;
	while (len)
	{
		i = process_string(str + i);
		if (!flag2 && check_triple_operator(str, i))
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
