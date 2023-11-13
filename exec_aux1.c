/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:59:29 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 15:02:31 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (*str == (char)c)
		return (str);
	return (NULL);
}

void	wait_exit(int status, t_stock *sts)
{
	if (WIFEXITED(status))
		sts->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (SIGINT == WTERMSIG(status))
		{
			sts->exit_status = SIGINT + 128;
			ft_putstr_fd("\n", 1);
		}
		else if (SIGQUIT == WTERMSIG(status))
			sts->exit_status = SIGQUIT + 128;
	}
}

void	quit_fct(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit : 3\n");
}

void	rd_exec_2(t_parse *cmd, t_listock *ls, t_exp **exp)
{
	if (cmd->output == -1)
	{
		exit (1);
		ls->sts->exit_status = 1;
	}
	else if (cmd->output > 1)
		dup2(cmd->output, 1);
	if (cmd->input == -1)
	{
		exit (1);
		ls->sts->exit_status = 1;
	}
	else if (cmd->input > 0)
		dup2(cmd->input, 0);
	if (builtin(cmd, exp, ls))
		exit (ls->sts->exit_status);
}

void	rd_exec1(t_parse *cmd, t_listock *ls, t_exp **exp, int arr)
{
	if (cmd->output == -1)
	{
		exit (1);
		ls->sts->exit_status = 1;
	}
	else if (cmd->output > 1)
		dup2(cmd->output, 1);
	else
		dup2(arr, 1);
	if (cmd->input == -1)
	{
		exit (1);
		ls->sts->exit_status = 1;
	}
	else if (cmd->input > 0)
		dup2(cmd->input, 0);
	if (builtin(cmd, exp, ls))
		exit (ls->sts->exit_status);
}
