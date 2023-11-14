/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:43:58 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/13 20:51:13 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handlewhitespaces(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	while (str[tokn->i] && (str[tokn->i] == ' ' || str[tokn->i] == '\t'))
		(tokn->i)++;
	dst[tokn->j] = ft_strdup1(" ", ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	regchars(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	while (str[tokn->i] && str[tokn->i] != ' ' && str[tokn->i] != '\t' && \
	str[tokn->i] != '<' && str[tokn->i] != '>' && str[tokn->i] != '|' && \
	str[tokn->i] != '\'' && str[tokn->i] != '"')
		(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	hndlipipe(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	while (str[tokn->i] && str[tokn->i] == '|')
		(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handleinput(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	while (str[tokn->i] && str[tokn->i] == '<')
		(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handle_output(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	while (str[tokn->i] && str[tokn->i] == '>')
		(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}
