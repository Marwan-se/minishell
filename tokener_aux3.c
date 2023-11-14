/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:44:58 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:34 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	determinelessthan(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] == '<')
	{
		flag = 4;
		break ;
	}
	return (flag);
}

int	determinegreaterthan(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] == '>')
	{
		flag = 5;
		break ;
	}
	return (flag);
}

int	determinesinglequote(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] == '\'')
	{
		flag = 6;
		break ;
	}
	return (flag);
}

int	determinedoublequote(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[*i] && str[*i] == '"')
	{
		flag = 7;
		break ;
	}
	return (flag);
}

int	determineflag(char *str, int *i)
{
	int	flag;

	flag = 0;
	flag = determinewhitespace(str, i);
	if (flag)
		return (flag);
	flag = determineregchars(str, i);
	if (flag)
		return (flag);
	flag = determinepipe(str, i);
	if (flag)
		return (flag);
	flag = determinelessthan(str, i);
	if (flag)
		return (flag);
	flag = determinegreaterthan(str, i);
	if (flag)
		return (flag);
	flag = determinesinglequote(str, i);
	if (flag)
		return (flag);
	flag = determinedoublequote(str, i);
	return (flag);
}
