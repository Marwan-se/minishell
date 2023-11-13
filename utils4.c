/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:16:17 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:08:28 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t	count, size_t	size)
{
	void	*mem;
	size_t	size1;

	size1 = count * size;
	mem = (void *)malloc(size1);
	if (!mem)
		exit (1);
	ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(mem));
	if (mem != NULL)
		ft_bzero(mem, size1);
	return (mem);
}

void	env_error(char **str)
{
	ft_putstr_fd(*str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(*(str + 1), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
}

void	cd_error(char	*str, t_stock *sts)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	sts->exit_status = 1;
}

char	*ft_strncpy2(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}
