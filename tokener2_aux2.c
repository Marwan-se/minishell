/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:30:06 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:45 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_to_expand(char *str, t_listock *ls, int fd, t_gc **ad)
{
	if (!ls->sts->quote_heredoc)
		str = expand_heredoc(str, ls, ad);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
}

int	heredoca(char *line, t_listock *ls, t_gc **ad)
{
	char	*str;
	int		fd[2];

	sigg_heredoc();
	pipe (fd);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, line))
		{
			ls->sts->exit_status = 0;
			break ;
		}
		if (!*str)
		{
			free(str);
			continue ;
		}
		check_to_expand(str, ls, fd[1], ad);
		free_me(str);
	}
	ft_reopen(str);
	close (fd[1]);
	execute_signals();
	return (fd[0]);
}

void	open_file_in(int *fd, t_cmd **lst, int *flag)
{
	if (fd[0] != 0)
		close(fd[0]);
	fd[0] = open((*lst)->data, O_RDONLY, 0666);
	if (fd[0] == -1)
	{
		*flag = 1;
		perror("Erreur lors de l'ouverture du fichier en lecture");
	}
}

void	open_file_out(int *fd, t_cmd **lst)
{
	if (fd[1] != 1)
		close(fd[1]);
	fd[1] = open((*lst)->data, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd[1] == -1)
		perror("Erreur lors de l'ouverture du fichier en écriture");
}

void	open_file_append(int *fd, t_cmd **lst)
{
	if (fd[1] != 1)
		close (fd[1]);
	fd[1] = open((*lst)->data, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd[1] == -1)
	{
		perror("Erreur lors de l'ouverture du fichier en écriture (append)");
	}
}
