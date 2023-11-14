/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:22:21 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/13 15:21:04 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_split(char *str, t_gc **ad)
{
	int		i;
	char	**src;
	int		ma;
	int		sh;

	if (!str)
		return (NULL);
	i = 0;
	sh = 0;
	ma = ft_count_words((char *)str, ':');
	src = malloc(sizeof(char *) * (ma + 1));
	if (!src)
		return (NULL);
	ft_lstadd_back22(ad, ft_lstnew22(src));
	while (sh < ma)
	{
		src[sh] = ft_get_next_word((char *) str, ':', &i, ad);
		if (!src[sh])
			return (free_all(src, sh));
		sh++;
	}
	src[sh] = NULL;
	return (src);
}

char	*path_env(char	**env, t_gc **ad)
{
	int		i;
	int		flag;
	char	*path;

	i = 0;
	flag = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag)
		path = ft_substr(env[i], 5, ft_strlen1(env[i]) - 5, ad);
	else
		path = NULL;
	return (path);
}

char	**split_path(char **env, t_gc **ad)
{
	char	**path;

	if (path_env(env, ad))
		path = ft_split(path_env(env, ad), ad);
	else
		path = NULL;
	return (path);
}

char	*valid_path(char	**paths, char	*str, t_gc **ad)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/", ad);
		temp = ft_strjoin(temp, str, ad);
		if (!access(temp, F_OK))
			break ;
		i++;
	}
	if (access(temp, F_OK))
		temp = NULL;
	return (temp);
}
