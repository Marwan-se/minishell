/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:43:58 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 16:09:02 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handlewhitespaces(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	dst[tokn->j] = ft_strdup1(" ");
	(tokn->j)++;
	tokn->flag = 0;
}

void	regchars(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && \
	str[*i] != '<' && str[*i] != '>' && str[*i] != '|' && \
	str[*i] != '\'' && str[*i] != '"')
		(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}

void	hndlipipe(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	while (str[*i] && str[*i] == '|')
		(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handleinput(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	while (str[*i] && str[*i] == '<')
		(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handle_output(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	while (str[*i] && str[*i] == '>')
		(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}
