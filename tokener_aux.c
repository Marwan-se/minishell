/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:42:59 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 09:54:28 by msekhsou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_single_quote(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	(tokn->i)++;
	while (str[tokn->i] && str[tokn->i] != '\'')
		(tokn->i)++;
	(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	handle_double_quote(char *str, char **dst, t_tok *tokn, t_gc **ad)
{
	tokn->k = tokn->i;
	(tokn->i)++;
	while (str[tokn->i] && str[tokn->i] != '"')
		(tokn->i)++;
	(tokn->i)++;
	dst[tokn->j] = ft_strndup(&str[tokn->k], tokn->i - tokn->k, ad);
	(tokn->j)++;
	tokn->flag = 0;
}

void	tok_cond(char *str, t_tok *tokn, char **dst, t_gc **ad)
{
	if (tokn->flag == 0)
		tokn->flag = determineflag(str, &(tokn->i));
	if (tokn->flag == 1 && (tokn->j < tokn->len))
		handlewhitespaces(str, dst, tokn, ad);
	else if (tokn->flag == 2 && (tokn->j < tokn->len))
		regchars(str, dst, tokn, ad);
	else if (tokn->flag == 3 && (tokn->j < tokn->len))
		hndlipipe(str, dst, tokn, ad);
	else if (tokn->flag == 4 && (tokn->j < tokn->len))
		handleinput(str, dst, tokn, ad);
	else if (tokn->flag == 5 && (tokn->j < tokn->len))
		handle_output(str, dst, tokn, ad);
	else if (tokn->flag == 6 && (tokn->j < tokn->len))
		handle_single_quote(str, dst, tokn, ad);
	else if (tokn->flag == 7 && (tokn->j < tokn->len))
		handle_double_quote(str, dst, tokn, ad);
}

char	**tokener_aux_loop(char *str, t_tok *tokn, t_gc **ad)
{
	char	**dst;

	dst = ft_calloc(sizeof(char *), tokn->len + 1, ad);
	if (!dst)
		return (NULL);
	while (tokn->len2 && (tokn->j < tokn->len))
	{
		tok_cond(str, tokn, dst, ad);
		tokn->len2--;
	}
	dst[tokn->len] = NULL;
	return (dst);
}

char	**tokener(char	*str, t_gc **ad)
{
	t_tok	tokn;

	tokn.i = 0;
	tokn.flag = 0;
	tokn.k = 0;
	tokn.j = 0;
	tokn.len2 = ft_strlen1(str);
	tokn.len = lenght(str);
	return (tokener_aux_loop(str, &tokn, ad));
}
