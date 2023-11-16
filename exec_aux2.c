/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:06:22 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:24 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exve_path_error(t_parse *cmd, t_listock *ls, char **env)
{
	if (cmd->data[0] && execve(cmd->data[0], cmd->data, env) == -1)
	{
		perror("execve");
		exit (127);
		ls->sts->exit_status = 127;
	}
}

void	command(t_parse *cmd, char **env, t_listock *ls, t_gc **ad)
{
	if (cmd->data[0] && !valid_path(split_path(env, ad), cmd->data[0], ad))
	{
		ft_putstr_fd("command not found\n", 2);
		exit (127);
		ls->sts->exit_status = 127;
	}
	else
	{
		if (cmd->data[0] && execve(valid_path(split_path(env, ad), \
		cmd->data[0], ad), cmd->data, env) == -1)
		{
			perror("execve");
			exit (127);
			ls->sts->exit_status = 127;
		}
	}
}

void	single_child_prc(t_parse *cmd, char **env, t_listock *ls, t_gc **ad)
{
	exec_handl();
	rd_exec_2(cmd, ls, ad);
	if (ft_strchr(cmd->data[0], '/'))
		exve_path_error(cmd, ls, env);
	else
		command(cmd, env, ls, ad);
}

void	perrorthefork(void)
{
	perror("fork");
	return ;
}

void	sig_plus_init(int *in, t_listock *ls, t_parse *cmd)
{
	protect();
	signal(SIGQUIT, quit_fct);
	*in = dup(0);
	ls->size = ft_lstsize(cmd);
}
