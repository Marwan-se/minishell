/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:59:16 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:04 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoin_with_equal(char *str1, char *str2, t_gc **ad)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen1(str1);
	len2 = ft_strlen1(str2);
	result = (char *)malloc(len1 + len2 + 2);
	if (!result)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(result));
	ft_strcpy(result, str1);
	result[len1] = '=';
	ft_strcpy(result + len1 + 1, str2);
	return (result);
}

void	join_auxiliaire(t_list	*tmp, char **result, t_gc **ad)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (tmp->value)
			result[i] = ft_strjoin_with_equal(tmp->name, tmp->value, ad);
		else if (!(tmp->value))
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
		i++;
	}
}

char	**join_name_and_value(t_list *lst, t_gc **ad)
{
	int		len;
	t_list	*tmp;
	char	**result;

	if (!lst)
		return (NULL);
	tmp = lst;
	len = ft_lstsize1(lst);
	while (tmp)
	{
		if (!(tmp->value))
			len--;
		tmp = tmp->next;
	}
	result = (char **)malloc(sizeof(char *) * (len + 1));
	if (!result)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(result));
	tmp = lst;
	join_auxiliaire(tmp, result, ad);
	result[len] = NULL;
	return (result);
}
