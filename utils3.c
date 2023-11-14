/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:55:57 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:55:02 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_tolower(int i)
{
	if (i >= 65 && i <= 90)
		i += 32;
	return (i);
}

int	echo_combinaison(char	*str)
{
	char	*echo;
	size_t	len;
	size_t	i;

	i = 0;
	echo = "echo";
	len = ft_strlen1(echo);
	if (ft_strlen1(str) != len)
		return (0);
	while (i < len)
	{
		if (ft_tolower(str[i]) != ft_tolower(echo[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*echo_combinaison2(char	*str)
{
	char	*echo;
	size_t	len;
	size_t	i;

	i = 0;
	echo = "echo";
	len = ft_strlen1(echo);
	if (ft_strlen1(str) != len)
		return (0);
	while (i < len)
	{
		if (ft_tolower(str[i]) != ft_tolower(echo[i]))
			return (0);
		i++;
	}
	return (echo);
}

int	pwd_combinaison(char	*str)
{
	char	*pwd;
	size_t	len;
	size_t	i;

	i = 0;
	pwd = "pwd";
	len = ft_strlen1(pwd);
	if (ft_strlen1(str) != len)
		return (0);
	while (i < len)
	{
		if (ft_tolower(str[i]) != ft_tolower(pwd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	env_combinaison(char	*str)
{
	char	*env;
	size_t	len;
	size_t	i;

	i = 0;
	env = "env";
	len = ft_strlen1(env);
	if (ft_strlen1(str) != len)
		return (0);
	while (i < len)
	{
		if (ft_tolower(str[i]) != ft_tolower(env[i]))
			return (0);
		i++;
	}
	return (1);
}
