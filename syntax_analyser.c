/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:57:21 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:26 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	is_quote(char *str, char quote)
{
	while (*str)
	{
		if (*str == quote)
			return (1);
		str++;
	}
	return (0);
}

int	check_quotes(char *str, char quote)
{
	if (quote)
		return (is_quote(str, quote));
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			if (check_quotes(++str, quote))
			{
				while (*str)
				{
					if (*str == quote)
						break ;
					str++;
				}
			}
			else
				return (0);
		}
		str++;
	}
	return (1);
}

int	check_end_op_pipe(char *str)
{
	int	len;

	len = ft_strlen1(str) - 1;
	while (str[len] && (str[len] == ' ' || str[len] == '\t'))
		len--;
	if (str[len] && (str[len] == '|' || str[len] == '>' || str[len] == '<'))
		return (1);
	return (0);
}

int	check_beg_pip(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] == '|')
		return (1);
	return (0);
}
