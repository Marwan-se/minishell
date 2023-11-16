/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:45:59 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:20:05 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	handle_flag(char *str, int *flag, int *i)
{
	if (*flag == 1)
	{
		*flag = 0;
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
	}
	if (*flag == 2 || *flag == 3)
	{
		*flag = 0;
		(*i) += second_third_flag(str + (*i), *flag);
	}
	if (*flag == 4 || *flag == 5)
	{
		*flag = 0;
		(*i) += fourth_fifth_flag(str + (*i), *flag);
	}
	if (*flag == 6 || *flag == 7)
	{
		*flag = 0;
		(*i) += sixth_seventh_flag(str + (*i), *flag);
	}
	return (*flag);
}

size_t	lenght(char *str)
{
	size_t	len;
	int		flag;
	int		len2;
	int		i;

	len = 0;
	flag = 0;
	len2 = ft_strlen1(str) + 1;
	i = 0;
	while (len2--)
	{
		if (flag == 0)
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			{
				len++;
				flag = 1;
				break ;
			}
			evaluate_character(str, &len, &flag, &i);
			handle_special_characters(str, &len, &flag, &i);
		}
		handle_flag(str, &flag, &i);
	}
	return (len);
}

int	determinewhitespace(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		flag = 1;
		break ;
	}
	return (flag);
}

int	determineregchars(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] != ' ' && \
	str[*i] != '\t' && str[*i] != '<' && \
	str[*i] != '>' && str[*i] != '|' && 
		str[*i] != '\'' && str[*i] != '"')
	{
		flag = 2;
		break ;
	}
	return (flag);
}

int	determinepipe(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] == '|')
	{
		flag = 3;
		break ;
	}
	return (flag);
}
