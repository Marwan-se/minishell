/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:03 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 12:23:33 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

int	ft_count_words(char *str, char separator)
{
	int	i;
	int	count;
	int	tmp;

	i = 0;
	count = 0;
	tmp = 1;
	while (str[i])
	{
		if (str[i] == separator)
			tmp = 1;
		if (str[i] != separator && tmp)
		{
			tmp = 0;
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_get_word_lenght(char *str, char separator, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != separator)
	{
		i++;
		j++;
	}
	return (j);
}

char	**free_all(char **tab, int i)
{
	while (i--)
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

char	*ft_get_next_word(char *str, char separator, int *i, t_gc **ad)
{
	int		index;
	char	*src;
	int		j;

	j = 0;
	index = *i;
	while (str[index] == separator)
		index++;
	src = malloc ((ft_get_word_lenght(str, separator, index) + 1)
			* sizeof(char));
	if (!src)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(src));
	while (str[index] && str[index] != separator)
	{
		src[j] = str[index];
		j++;
		index++;
	}
	src[j] = '\0';
	*i = index;
	return (src);
}
