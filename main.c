/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:25:23 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 23:23:14 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	main_exec(t_listock *ls, t_list *lst, char *str, t_stock *sts)
{
	ls->my_env = join_name_and_value(lst);
	str = expand_variables(str, ls);
	flag_heredoc_quote(str, sts);
	ls->tmp = list(tokener(str), &(ls->head));
	join_rd_del(&(ls->tmp));
	ls->liste = parse(ls->tmp, ls);
	if (!g_end_heredoc)
		execution(ls->liste, ls->my_env, &(ls->exp), ls);
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
	//free (line);
	//free (str);
	(void)str;
	(void)line;
}

void	string_history_rdln(char **str, char *line)
{
	*str = no_space_beg_end(line);
	add_history(*str);
}

t_listock	*allocate_ls(t_listock **ls, t_stock *sts, t_list **lst)
{
	*ls = malloc(sizeof(t_listock));
	if (!*ls)
		exit (1);
	ft_lstadd_back22(&g_gg.lst_clct, ft_lstnew22(*ls));
	(*ls)->sts = sts;
	(*ls)->lst = lst;
	return (*ls);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*lst;
	t_stock		sts;
	t_listock	*ls;
	char		*str;

	lst = NULL;
	ls = allocate_ls(&ls, &sts, &lst);
	main_init(ls, ac, av);
	env_list(&lst, env);
	main_sig();
	while (1)
	{
		g_end_heredoc = 0;
		line = readline("Alexabash:$ ");
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		string_history_rdln(&str, line);
		if (!check_syntax(str, &sts))
			main_exec(ls, lst, str, &sts);
		main_null_free(str, line, ls);
		free(line);
	}
	ft_lstclear(&g_gg.lst_clct);
}
