/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:42:59 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/12 16:11:36 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_single_quote(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handle_double_quote(char *str, int *i, char **dst, t_tok *tokn)
{
	tokn->k = *i;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	(*i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], *i - tokn->k);
	(tokn->j)++;
	tokn->flag = 0;
}

void	tok_cond(char *str, t_tok *tokn, int *i, char **dst)
{
	if (tokn->flag == 0)
		tokn->flag = determineflag(str, i);
	if (tokn->flag == 1 && (tokn->j < tokn->len))
		handlewhitespaces(str, i, dst, tokn);
	else if (tokn->flag == 2 && (tokn->j < tokn->len))
		regchars(str, i, dst, tokn);
	else if (tokn->flag == 3 && (tokn->j < tokn->len))
		hndlipipe(str, i, dst, tokn);
	else if (tokn->flag == 4 && (tokn->j < tokn->len))
		handleinput(str, i, dst, tokn);
	else if (tokn->flag == 5 && (tokn->j < tokn->len))
		handle_output(str, i, dst, tokn);
	else if (tokn->flag == 6 && (tokn->j < tokn->len))
		handle_single_quote(str, i, dst, tokn);
	else if (tokn->flag == 7 && (tokn->j < tokn->len))
		handle_double_quote(str, i, dst, tokn);
}

char	**tokener_aux_loop(char *str, t_tok *tokn, int *i)
{
	char	**dst;

	dst = ft_calloc(sizeof(char *), tokn->len + 1);
	if (!dst)
		return (NULL);
	while (tokn->len2 && (tokn->j < tokn->len))
	{
		tok_cond(str, tokn, i, dst);
		tokn->len2--;
	}
	dst[tokn->len] = NULL;
	return (dst);
}

char	**tokener(char	*str)
{
	int		i;
	t_tok	tokn;

	i = 0;
	tokn.flag = 0;
	tokn.k = 0;
	tokn.j = 0;
	tokn.len2 = ft_strlen1(str);
	tokn.len = lenght(str);
	return (tokener_aux_loop(str, &tokn, &i));
}
