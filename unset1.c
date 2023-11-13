/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:56:36 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 22:09:37 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void	my_//free(t_list *current)
// {
// 	//free(current->name);
// 	//free(current->value);
// 	//free(current);
// }

void	delete_by_position(t_list **head, int pos)
{
	t_list	*current;
	t_list	*previous;

	current = *head;
	previous = NULL;
	if (!*head)
		return ;
	else if (pos == 0)
	{
		*head = current->next;
		return ;
	}
	else
	{
		while (pos != 0)
		{
			previous = current;
			current = current->next;
			pos--;
		}
		previous->next = current->next;
	}
}

void	unset_set(t_list **lst, char **av, t_stock *sts)
{
	int		j;
	t_list	*temp;

	sts->exit_status = 0;
	temp = *lst;
	j = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->name, *av))
		{
			delete_by_position(lst, j);
			break ;
		}
		temp = temp->next;
		j++;
	}
}

void	unset_auxiliaire(char **av, t_list **lst, t_stock *sts)
{
	char	**str;

	str = av + 1;
	while (*str)
	{
		if (checck_syntax(*str))
		{
			(printf_for_unset(*str));
			sts->exit_status = 1;
		}
		else
			unset_set(lst, str, sts);
		str++;
	}
}

int	unset(char **av, t_list **lst, t_stock *sts)
{
	if (*av && !ft_strcmp(*av, "unset") && *(av + 1))
		unset_auxiliaire(av, lst, sts);
	if (*av && !ft_strcmp(*av, "unset") && !*(av + 1))
		return (2);
	return (0);
}
