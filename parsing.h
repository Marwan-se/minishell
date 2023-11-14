/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadria- <shadria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:58:02 by shadria-          #+#    #+#             */
/*   Updated: 2023/11/14 16:04:43 by shadria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> 

enum e_types{
	pip,
	word,
	spaces,
	rd_input,
	rd_output,
	rd_append,
	heredoc,
	dbl_quotes,
	sgl_quotes,
	file_in,
	file_out,
	file_append,
	lim
};

int	g_end_heredoc;

typedef struct s_parse{
	struct s_parse	*next;
	char			**data;
	int				input;
	int				output;
}	t_parse;

typedef struct s_cmd{
	struct s_cmd	*next;
	struct s_cmd	*previous;
	char			*data;
	int				type;
}	t_cmd;

typedef struct s_list
{
	struct s_list	*next;
	char			*name;
	char			*value;
}	t_list;

typedef struct s_exp
{
	struct s_exp	*next;
	char			*content;
}				t_exp;

typedef struct s_stock{
	int	quote_heredoc;
	int	exit_status;
}t_stock;

typedef struct s_listock{
	t_stock		*sts;
	int			flag;
	t_list		*tmpp;
	t_list		**lst;
	t_exp		*exp;
	t_parse		*liste;
	t_cmd		*head;
	t_cmd		*tmp;
	int			len;
	char		**my_env;
	char		**input;
	int			flagg;
	char		*line;
	char		*str;
	int			size;
}t_listock;

typedef struct s_variables{
	char	*result;
	char	*res_ptr;
	char	*value;
	char	k;
	int		i;
	int		flag;
	int		flag_to_heredoc;
	int		flag_word;
	int		inside_single_quote;
	char	*variable_namee;
}t_variables;

typedef struct s_tok{
	int		k;
	int		i;
	int		len2;
	size_t	len;
	size_t	j;
	int		flag;
}t_tok;

typedef struct s_gc
{
	struct s_gc	*next;
	void		*content;
}				t_gc;

void		free_me(char *str);
void		sigg_heredoc(void);
void		quit_handler(char *executable);
void		ft_lstadd_back22(t_gc **lst, t_gc *new);
void		ft_lstdelone(t_gc *lst);
void		ft_lstclear(t_gc **lst);
t_gc		*ft_lstnew22(void *content);
t_gc		*ft_lstlast22(t_gc *lst);
void		main_sig(void);
void		quit_fct(int sig);
int			ft_lstsize(t_parse *lst);
void		join_words(t_cmd **lst, t_gc **ad);
void		deletenode(t_cmd **head, t_cmd *lst);
void		the_main_exec(t_listock *ls, t_gc **ad);
char		*ft_strjoin(char *s1, char *s2, t_gc **ad);
int			lexer(char	*str);
size_t		ft_strnlen(const char *s, size_t n);
char		*no_space_beg_end(char	*str, t_gc **ad);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		check_to_expand(char *str, t_listock *ls, int fd, t_gc **ad);
int			heredoca(char *line, t_listock *ls, t_gc **ad);
void		open_file_in(int *fd, t_cmd **lst, int *flag);
void		open_file_out(int *fd, t_cmd **lst);
void		open_file_append(int *fd, t_cmd **lst);
void		perrorthefork(void);
t_parse		*parse(t_cmd *lst, t_listock *ls, t_gc **ad);
char		*ft_strchr(const char *s, int c);
void		main_init(t_listock	*ls, int ac, char **av);
void		command(t_parse *cmd, char **env, t_listock *ls, t_gc **ad);
void		exve_path_error(t_parse *cmd, t_listock *ls, char **env);
void		sig_plus_init(int *in, t_listock *size, t_parse *cmd);
void		main_exec(t_listock *ls, char *str, t_stock *sts, t_gc **ad);
void		rd_exec1(t_parse *cmd, t_listock *ls, int arr, t_gc **ad);
void		rd_exec_2(t_parse *cmd, t_listock *ls, t_gc **ad);
void		wait_exit(int status, t_stock *sts);
void		execution(t_parse *cmd, char **env, t_listock *ls, t_gc **ad);
void		single_child_prc(t_parse *cmd, \
char **env, t_listock *ls, t_gc **ad);
void		exec_built(t_parse *cmd, t_listock *ls, t_gc **ad);
void		exec_cmd_single(t_parse *cmd, char **env, \
t_listock *ls, t_gc **ad);
void		exec_cmd_pip(t_parse *cmd, char **env, t_listock *ls, t_gc **ad);
void		dup_close(int arr0, int arr1);
void		dup_close_wait(int in, t_listock *ls);
void		main_null_free(char *str, char *line, t_listock *ls);
void		string_history_rdln(char **str, char *line, t_gc **ad);
t_listock	*allocate_ls(t_listock **ls, t_stock *sts, t_list **lst, t_gc **ad);
int			builtin(t_parse *ls, t_listock *lss, t_gc **ad);
void		handle_export2(char **str, t_listock *lss, t_parse *ls, t_gc **ad);
void		handle_unset2(char **str, t_listock *lss);
int			builtin2(t_parse *ls, t_listock *lss, t_gc **ad);
void		handle_env(char **str, t_parse *ls, t_listock *lss);
void		handle_pwd(t_listock *lss, t_parse *ls, t_gc **ad);
void		handle_cd(char **str, char *pwd, \
t_listock *lss, t_gc **ad);
void		handle_export(char **str, t_listock *lss, \
t_parse *ls, t_gc **ad);
int			ft_count_words(char *str, char separator);
void		cd_home(t_stock *sts);
void		handle_echo(char **str, t_parse *ls, t_listock *lss);
void		*ft_calloc(size_t	count, size_t	size, t_gc **ad);
void		perrorat(void);
void		update_oldpwd_cd(t_list *lst, char *currentDir, t_gc **ad);
void		update_pwd_cd(t_list *lst, char *NEW_PWD, t_gc **ad);
int			cd_auxiliaire(char **av, t_stock *sts);
char		*expand_variables(char *input, t_listock *ls, t_gc **ad);
char		*ft_getenv(t_list *lst, const char	*variable_name);
void		env(int ac, char **av, t_list **lst, t_parse **ls);
t_cmd		*add_back(t_cmd *head, char *data, t_gc **ad);
char		*valid_path(char	**paths, char	*str, t_gc **ad);
char		**split_path(char **env, t_gc **ad);
void		join_rd_del(t_cmd **lst, t_gc **ad);
t_cmd		*list(char **str, t_cmd	**lst, t_gc **ad);
int			check_syntax(char	*str, t_stock *sts);
char		*ft_substr(char const *s, unsigned int start, \
size_t len, t_gc **ad);
int			lexer(char	*str);
void		ft_putstr_fd(char *s, int fd);
t_parse		*ft_lstnew(char **content, int in, int out, t_gc **ad);
t_parse		*ft_lstlast(t_parse *lst);
void		ft_lstadd_back(t_parse **lst, t_parse *new);
int			ft_isdigit(int i);
int			ft_isalpha(int c);
char		*ft_itoa(int n, t_gc **ad);
void		ft_strcpy(char	*dest, char	*src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strndup(const char *s, int n, t_gc **ad);
char		*ft_strdup1(const char *s, t_gc **ad);
void		ft_lstadd_back1(t_list **lst, t_list *new);
t_list		*ft_lstlast1(t_list *lst);
t_list		*ft_lstnew1(char *name, char *value, t_gc **ad);
void		env_list(t_list **lst, char **environnement, t_gc **ad);
char		**split_souad(char *line_env, t_gc **ad);
void		shlvl_increment(t_list **lst, t_gc **ad);
void		the_pwd_print(t_list **lst, t_gc **ad);
void		the_oldpwd_print(t_list **lst, t_gc **ad);
void		handle_flags(char **input, int *flag);
void		the_eight_dash(t_list **lst, t_gc **ad);
void		handle_variable(char *variable_name, \
t_listock *ls, char **res_ptr, t_gc **ad);
char		*expand_heredoc(char *input, t_listock *ls, t_gc **ad);
void		flag_heredoc_quote(char	*str, t_stock *sts);
void		fill_stack_var(t_variables	*var, char **inpute, \
char	*variable_name);
void		execute_signals(void);
void		exec_handl(void);
void		protect(void);
void		sig_close(int sig);
void		ft_cd(char *pwd, char **av, t_listock *ls, t_gc **ad);
void		ft_echo(char **av, t_parse **lst, t_stock *sts);
int			echo_combinaison(char	*str);
void		printf_for_unset(char *str);
char		**join_name_and_value(t_list *lst, t_gc **ad);
int			env_combinaison(char	*str);
int			pwd_combinaison(char	*str);
int			unset(char **av, t_list **lst, t_stock *sts);
void		pwdd(char *pwd, t_parse	**ls);
void		export1(t_exp *list, t_list *lst, t_parse **ls, t_gc **ad);
void		case2(t_listock *ls, int j, char *str, t_gc **ad);
void		case1(t_listock *ls, int j, char *str, t_gc **ad);
void		env_update3(t_listock *ls, char *name, t_gc **ad);
void		env_update2(t_listock *ls, char *name, \
char *value, t_gc **ad);
void		env_update1(t_listock *ls, char *name, \
char *value, t_gc **ad);
char		*ft_strjoin1(char *s1, char *s2, t_gc **ad);
void		ft_lstadd_back2(t_exp **lst, t_exp *new);
t_exp		*ft_lstlast2(t_exp *lst);
t_exp		*ft_lstnew2(char *content, t_gc **ad);
size_t		ft_strlen1(const char *s);
int			checck_syntax(char *str);
void		printf_for_unset(char *str);
void		printf_and_free(char *name, char *value);
int			env_updates(char **av, t_listock *ls, t_gc **ad);
void		cd_error(char	*str, t_stock *sts);
char		*ft_strncpy(char *s1, char *s2, int n);
int			ft_lstsize1(t_list *lst);
int			string_dig(char *str);
void		exit1(char **av, t_stock *sts);
char		*ft_strncpy2(char *s1, char *s2, int n);
void		cd_aux2(char *c, char **n, t_gc **ad);
void		cd_aux(char **av, t_stock *sts, int *flag);
void		env_error(char **str);
char		*ft_get_next_word(char *str, char separator, int *i, t_gc **ad);
char		**free_all(char **tab, int i);
void		ft_reopen(char *str);
size_t		handle_flag(char *str, int *flag, int *i);
size_t		lenght(char *str);
int			determinewhitespace(char *str, int *i);
int			determineregchars(char *str, int *i);
int			determinepipe(char *str, int *i);
int			determineflag(char *str, int *i);
int			determinedoublequote(char *str, int *i);
int			determinesinglequote(char *str, int *i);
int			determinegreaterthan(char *str, int *i);
int			determinelessthan(char *str, int *i);
void		handle_output(char *str, char **dst, t_tok *tokn, t_gc **ad);
void		handleinput(char *str, char **dst, t_tok *tokn, t_gc **ad);
void		hndlipipe(char *str, char **dst, t_tok *tokn, t_gc **ad);
void		regchars(char *str, char **dst, t_tok *tokn, t_gc **ad);
void		handlewhitespaces(char *str, char **dst, \
t_tok *tokn, t_gc **ad);
char		**tokener(char	*str, t_gc **ad);
char		**tokener_aux_loop(char *str, t_tok *tokn, t_gc **ad);
void		tok_cond(char *str, t_tok *tokn, char **dst, t_gc **ad);
void		handle_double_quote(char *str, char **dst, \
t_tok *tokn, t_gc **ad);
void		handle_single_quote(char *str, char **dst, \
t_tok *tokn, t_gc **ad);
void		handle_special_characters(char *str, size_t *len, \
int *flag, int *i);
size_t		second_third_flag(char *str, int flag);
size_t		fourth_fifth_flag(char *str, int flag);
size_t		sixth_seventh_flag(char *str, int flag);
void		evaluate_character(char *str, size_t *len, int *flag, int *i);
void		is_inside_quotes(char *str, int index, int *flag2, char *quote);
int			pip_after_pip(char *str);
int			check_pip(char *str, int *i, int *flag);
void		check_quote(char *str, int *i, char *quote, int *flag2);
int			slash_vgl(char *str);
int			op_op_no_space(char *str);
int			process_string(char *str);
int			check_triple_operator(char *str, int i);
int			op_before_pip(char *str);
int			check_operator(char *str, int index, char operator, int *flag);
int			check_syntax(char	*str, t_stock *sts);
int			op_op_space(char *str);
int			check_conditions(char *str, int *index, int flag2);
int			check_brackets(char *str, int *i);
int			chk_quote(char *str, int *i, int *flag2, char *quote);
int			check_beg_pip(char	*str);
int			check_end_op_pipe(char *str);
int			check_quotes(char *str, char quote);
int			is_quote(char *str, char quote);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
