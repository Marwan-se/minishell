/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:10:00 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 15:10:38 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	dup_close_wait(int in, t_listock *ls)
{
	int	status;

	dup2 (in, 0);
	close (in);
	while (wait(&status) != -1)
		;
	wait_exit(status, ls->sts);
	execute_signals();
}

void	dup_close(int arr0, int arr1)
{
	dup2(arr0, 0);
	close(arr1);
	close(arr0);
}

void	exec_cmd_pip(t_parse *cmd, char **env, t_listock *ls)
{
	if (cmd->data[0][0] == '/')
		exve_path_error(cmd, ls, env);
	else
		command(cmd, env, ls);
}

void	exec_cmd_single(t_parse *cmd, char **env, t_listock *ls, t_exp **exp)
{
	int	uid;

	uid = fork();
	if (uid == 0)
		single_child_prc(cmd, exp, env, ls);
	else if (uid == -1)
		perrorthefork();
}

void	exec_built(t_parse *cmd, t_listock *ls)
{
	if (builtin2(cmd, ls))
		return (execute_signals());
}
