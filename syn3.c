/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:56:06 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:19:32 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	slash_vgl(char *str)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			flag = 1;
			quote = str[i];
		}
		else if (flag == 1 && str[i] == quote)
			flag = 0;
		if ((!flag && str[i] == ';') || str[i] == '\\')
			break ;
		i++;
	}
	if (str[i] && (str[i] == ';' || str[i] == '\\'))
		return (1);
	return (0);
}

void	check_quote(char *str, int *i, char *quote, int *flag2)
{
	if (*flag2 == 0 && (str[*i] == '\'' || str[*i] == '"'))
	{
		*flag2 = 1;
		*quote = str[*i];
	}
	else if (*flag2 == 1 && str[*i] == *quote)
		*flag2 = 0;
	(*i)++;
}

int	check_pip(char *str, int *i, int *flag)
{
	int	flag2;

	flag2 = 0;
	if (!flag2 && str[*i] && str[*i] == '|')
	{
		if (str[*i + 1] && (str[*i + 1] == ' ' || str[*i + 1] == '\t'))
		{
			(*i)++;
			while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
				(*i)++;
			if (str[*i] && str[*i] == '|')
				*flag = 1;
			return (1);
		}
		else if (str[*i + 1] && str[*i + 1] == '|')
		{
			*flag = 1;
			return (1);
		}
	}
	return (0);
}

int	pip_after_pip(char *str)
{
	int		i;
	int		len;
	int		flag;
	int		flag2;
	char	quote;

	flag2 = 0;
	flag = 0;
	len = ft_strlen1(str);
	i = 0;
	while (len)
	{
		while (str[i] && str[i] != '|')
		{
			check_quote(str, &i, &quote, &flag2);
		}
		if (check_pip(str, &i, &flag))
			break ;
		if (str[i])
			i++;
		len--;
	}
	return (flag);
}

void	is_inside_quotes(char *str, int index, int *flag2, char *quote)
{
	if (*flag2 == 0 && (str[index] == '\'' || str[index] == '"'))
	{
		*flag2 = 1;
		*quote = str[index];
	}
	else if (*flag2 == 1 && str[index] == *quote)
	{
		*flag2 = 0;
	}
}
