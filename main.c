/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:25:23 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 15:50:28 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	main_exec(t_listock *ls, char *str, t_stock *sts, t_gc **ad)
{
	ls->my_env = join_name_and_value(*(ls->lst), ad);
	str = expand_variables(str, ls, ad);
	flag_heredoc_quote(str, sts);
	ls->tmp = list(tokener(str, ad), &(ls->head), ad);
	join_rd_del(&(ls->tmp), ad);
	ls->liste = parse(ls->tmp, ls, ad);
	if (!g_end_heredoc && ls->liste)
		execution(ls->liste, ls->my_env, ls, ad);
	else if (g_end_heredoc)
		sts->exit_status = 1;
	while (ls->liste)
	{
		if (ls->liste->input != 0)
			close(ls->liste->input);
		if (ls->liste->output != 1)
			close(ls->liste->output);
		ls->liste = ls->liste -> next;
	}
}

void	main_null_free(char *str, char *line, t_listock *ls)
{
	ls->tmp = NULL;
	ls->head = NULL;
	ls->liste = NULL;
	(void)str;
	(void)line;
}

void	string_history_rdln(char **str, char *line, t_gc **ad)
{
	add_history(line);
	*str = no_space_beg_end(line, ad);
}

t_listock	*allocate_ls(t_listock **ls, t_stock *sts, t_list **lst, t_gc **ad)
{
	*ls = malloc(sizeof(t_listock));
	if (!*ls)
		exit (1);
	ft_lstadd_back22(ad, ft_lstnew22(*ls));
	(*ls)->sts = sts;
	(*ls)->lst = lst;
	return (*ls);
}

int	main(int ac, char **av, char **env)
{
	t_list		*lst;
	t_stock		sts;
	t_listock	*ls;
	t_gc		*ad;

	lst = NULL;
	ad = NULL;
	ls = allocate_ls(&ls, &sts, &lst, &ad);
	main_init(ls, ac, av);
	g_end_heredoc = 0;
	env_list(&lst, env, &ad);
	while (1)
	{
		ls->line = readline("Alexabash:$ ");
		if (!ls->line)
			break ;
		if (!*ls->line)
		{
			free(ls->line);
			continue ;
		}
		the_main_exec(ls, &ad);
	}
	ft_lstclear(&ad);
}
