/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:20 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:52:22 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (!str[i] && str[i - 1] == 'n')
			return (1);
	}
	return (0);
}

void	echo_auxiliaire(char **av, int fileout)
{
	char	**str;

	str = av + 1;
	while (*str)
	{
		ft_putstr_fd(*str, fileout);
		if (*(str + 1))
			write (fileout, " ", 1);
		str++;
	}
	ft_putstr_fd("\n", fileout);
}

void	echo_auxiliaire2(char **av, int outfile)
{
	ft_putstr_fd(*av, outfile);
	if (*(av + 1))
		write (outfile, " ", 1);
}

void	echo_auxiliaire3(char **av, int outfile)
{
	char	**str;

	str = NULL;
	if (*(av + 1))
		str = av + 2;
	while (*str)
	{
		if (*(str + 1) && option(*str))
			str++;
		else
			break ;
	}
	while (str && *str)
	{
		echo_auxiliaire2(str, outfile);
		str++;
	}
}

void	ft_echo(char **av, t_parse **lst, t_stock *sts)
{
	if (*av && echo_combinaison(*av))
	{
		if (!*(av + 1))
			ft_putstr_fd("\n", (*lst)->output);
		else
		{
			if (*(av + 1) && option(*(av + 1)))
				echo_auxiliaire3(av, (*lst)->output);
			else
			{
				echo_auxiliaire(av, (*lst)->output);
			}
		}
		sts->exit_status = 0;
	}
}
