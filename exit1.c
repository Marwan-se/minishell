/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:53 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:55 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	string_dig(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
		{
			flag = 1;
			break ;
		}
	}
	return (flag);
}

void	exit_auxiliaire1(t_stock *sts)
{
	ft_putstr_fd("exit\n", 1);
	sts->exit_status = 0;
	exit(0);
}

void	exit_auxiliaire2(char **av, char c, t_stock *sts)
{
	char	**str;

	str = av + 1;
	if (*str && string_dig(*str))
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(*str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sts->exit_status = 255;
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		c = atoi(*str);
		sts->exit_status = c;
		exit(c);
	}
}

void	exit_auxiliaire3(char **av, t_stock *sts)
{
	char	**str;

	str = av + 1;
	if (!string_dig(*str))
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 1);
		sts->exit_status = 1;
	}
	else if (string_dig(*str))
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(*str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		sts->exit_status = 255;
		exit(255);
	}
}

void	exit1(char **av, t_stock *sts)
{
	char		c;

	c = 0;
	if (*av && !*(av + 1) && !ft_strcmp(*av, "exit"))
		exit_auxiliaire1(sts);
	if (*av && *(av + 1) && !*(av + 2) && !ft_strcmp(*av, "exit"))
		exit_auxiliaire2(av, c, sts);
	if (*av && *(av + 1) && *(av + 2) && !ft_strcmp(*av, "exit"))
		exit_auxiliaire3(av, sts);
}
