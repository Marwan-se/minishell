/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:05:54 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:38 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	evaluate_character(char *str, size_t *len, int *flag, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<' && \
			str[*i] != '>' && str[*i] != '|' && str[*i] != '\'' && \
		str[*i] != '"')
	{
		(*len)++;
		(*flag) = 2;
		(*i)++;
		break ;
	}
	while (str[*i] && str[*i] == '|')
	{
		(*len)++;
		(*flag) = 3;
		(*i)++;
		break ;
	}
	while (str[*i] && str[*i] == '<')
	{
		(*len)++;
		(*flag) = 4;
		(*i)++;
		break ;
	}
}

size_t	sixth_seventh_flag(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag == 6)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (flag == 7)
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		i++;
	}
	return (i);
}

size_t	fourth_fifth_flag(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag == 4)
	{
		while (str[i] && str[i] == '<')
			i++;
	}
	if (flag == 5)
	{
		while (str[i] && str[i] == '>')
			i++;
	}
	return (i);
}

size_t	second_third_flag(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag == 2)
	{
		flag = 0;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && \
			str[i] != '<' && str[i] != '>' && str[i] != '|' && \
			str[i] != '\'' && str[i] != '"')
			i++;
	}
	if (flag == 3)
	{
		flag = 0;
		while (str[i] && str[i] == '|')
			i++;
	}
	return (i);
}

void	handle_special_characters(char *str, size_t *len, int *flag, int *i)
{
	while (str[*i] && str[*i] == '>')
	{
		(*len)++;
		*flag = 5;
		break ;
	}
	while (str[*i] && str[*i] == '\'')
	{
		(*len)++;
		*flag = 6;
		break ;
	}
	while (str[*i] && str[*i] == '"')
	{
		(*len)++;
		*flag = 7;
		break ;
	}
}
