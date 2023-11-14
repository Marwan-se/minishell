/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:59 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/13 23:13:41 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	rd_ex_cl(t_parse *cmd, t_listock *ls, int *arr, t_gc **ad)
{
	exec_handl();
	close(arr[0]);
	rd_exec1(cmd, ls, arr[1], ad);
}

void	protct_and_pip(t_parse *cmd, int *arr, int *uid)
{
	if (!cmd->data[0])
		return ;
	protect();
	pipe(arr);
	*uid = fork();
}

void	execution(t_parse *cmd, char **env, t_listock *ls, t_gc **ad)
{
	int		arr[2];
	int		uid;
	int		in;

	sig_plus_init(&in, ls, cmd);
	while (cmd->next)
	{
		protct_and_pip(cmd, arr, &uid);
		if (uid == 0)
		{
			rd_ex_cl(cmd, ls, arr, ad);
			exec_cmd_pip(cmd, env, ls, ad);
		}
		else if (uid == -1)
			return (perrorthefork(), dup_close_wait(in, ls));
		dup_close(arr[0], arr[1]);
		cmd = cmd->next;
	}
	if (ls->size == 1)
		if (builtin2(cmd, ls, ad))
			return (execute_signals());
	exec_cmd_single(cmd, env, ls, ad);
	dup_close_wait(in, ls);
}

void	main_init(t_listock	*ls, int ac, char **av)
{
	(void)ac;
	(void)av;
	ls->exp = NULL;
	ls->tmp = NULL;
	ls->liste = NULL;
	ls->head = NULL;
	ls->str = NULL;
	main_sig();
}

void	main_sig(void)
{
	rl_catch_signals = 0;
	execute_signals();
}
