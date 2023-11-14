/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:14:17 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:34 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	case2(t_listock *ls, int j, char *str, t_gc **ad)
{
	char	*name;
	char	*value;

	j = 0;
	while (str[j] && str[j] != '+')
		j++;
	if (str[j] == '+' && str[j + 1] == '=')
	{
		name = ft_strndup(str, j, ad);
		value = ft_strdup1(str + j + 2, ad);
		env_update2(ls, name, value, ad);
	}
	else
	{
		name = ft_strdup1(str, ad);
		env_update3(ls, name, ad);
	}
}
