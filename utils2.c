/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:56:17 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:20:55 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_lenght(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_strfill(char *str, unsigned int n, int len)
{
	while (n > 0)
	{
		str[len] = 48 + (n % 10);
		len--;
		n = n / 10;
	}
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*so1;
	unsigned char	*so2;
	size_t			i;

	i = 0;
	so1 = (unsigned char *)s1;
	so2 = (unsigned char *)s2;
	while (so1[i] || so2[i])
	{
		if (so1[i] != so2[i])
			return (so1[i] - so2[i]);
		i++;
	}
	return (0);
}

char	*ft_itoa(int n, t_gc **ad)
{
	char	*str;
	size_t	len;

	len = ft_lenght(n);
	str = (char *)ft_calloc((len + 1), sizeof(char), ad);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	str = ft_strfill(str, n, len - 1);
	return (str);
}

void	ft_strcpy(char	*dest, char	*src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
