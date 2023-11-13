/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:06:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 15:06:59 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exve_path_error(t_parse *cmd, t_listock *ls, char **env)
{
	if (execve(cmd->data[0], cmd->data, env) == -1)
	{
		perror("execve");
		exit (127);
		ls->sts->exit_status = 127;
	}
}

void	command(t_parse *cmd, char **env, t_listock *ls)
{
	if (!valid_path(split_path(env), cmd->data[0]))
	{
		ft_putstr_fd("command not found\n", 2);
		exit (127);
		ls->sts->exit_status = 127;
	}
	else
	{
		if (execve(valid_path(split_path(env), \
		cmd->data[0]), cmd->data, env) == -1)
		{
			perror("execve");
			exit (127);
			ls->sts->exit_status = 127;
		}
	}
}

void	single_child_prc(t_parse *cmd, t_exp **exp, char **env, t_listock *ls)
{
	exec_handl();
	rd_exec_2(cmd, ls, exp);
	if (ft_strchr(cmd->data[0], '/'))
		exve_path_error(cmd, ls, env);
	else
		command(cmd, env, ls);
}

void	perrorthefork(void)
{
	perror("fork");
	return ;
}

void	sig_plus_init(int *in, int *size, t_parse *cmd)
{
	protect();
	signal(SIGQUIT, quit_fct);
	*in = dup(0);
	*size = ft_lstsize(cmd);
}
