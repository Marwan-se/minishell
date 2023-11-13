/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:14:17 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 15:15:00 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	case2(t_list *tmp, t_listock *ls, int j, char *str)
{
	char	*name;
	char	*value;

	j = 0;
	while (str[j] && str[j] != '+')
		j++;
	if (str[j] == '+' && str[j + 1] == '=')
	{
		name = ft_strndup(str, j);
		value = ft_strdup1(str + j + 2);
		env_update2(tmp, ls, name, value);
	}
	else
	{
		name = ft_strdup1(str);
		env_update3(tmp, ls, name);
	}
}
