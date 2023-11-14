/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:22:30 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 15:50:00 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	the_main_exec(t_listock *ls, t_gc **ad)
{
	if (g_end_heredoc == -1)
	{
		ls->sts->exit_status = 1;
		g_end_heredoc = 0;
	}
	string_history_rdln(&(ls->str), ls->line, ad);
	if (!check_syntax(ls->str, ls->sts))
		main_exec(ls, ls->str, ls->sts, ad);
	main_null_free(ls->str, ls->line, ls);
	free(ls->line);
}

void	sigg_heredoc(void)
{
	protect();
	signal(SIGINT, sig_close);
}

void	quit_handler(char *executable)
{
	protect();
	if (ft_strcmp(executable, "./minishell"))
		signal(SIGQUIT, quit_fct);
}
