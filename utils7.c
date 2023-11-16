/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:25:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:21:27 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strdup1(const char *s, t_gc **ad)
{
	int		i;
	char	*src;
	char	*dst;

	src = (char *)s;
	dst = malloc(sizeof(char) * (ft_strlen1(src) + 1));
	if (dst == NULL)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(dst));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*no_space_beg_end(char	*str, t_gc **ad)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	j = 0;
	i = 0;
	dst = NULL;
	len = ft_strlen1(str);
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	j = i;
	while (len > j && (str[len - 1] == '\t' || str[len - 1] == ' '))
		len--;
	if (len >= j)
		dst = ft_strndup(&str[j], len - j, ad);
	return (dst);
}

void	ft_reopen(char *str)
{
	int	fd;

	free_me(str);
	if (ttyname(0) == 0)
	{
		fd = open(ttyname(1), O_RDONLY);
		dup2(0, fd);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*so1;
	unsigned char	*so2;
	size_t			i;

	i = 0;
	so1 = (unsigned char *)s1;
	so2 = (unsigned char *)s2;
	while ((so1[i] || so2[i]) && i < n)
	{
		if (so1[i] != so2[i])
			return (so1[i] - so2[i]);
		i++;
	}
	return (0);
}

void	free_me(char *str)
{
	if (str)
		free(str);
}
