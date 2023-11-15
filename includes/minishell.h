/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:48:24 by educlos           #+#    #+#             */
/*   Updated: 2023/11/15 17:55:50 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_pars
{
	char	**cmd;
	int	infile;
	int outfile;
	int	append;
	char	**delimiter;
	struct s_pars	*next;
	struct s_pars	*prev;
	char **envp;
}					t_pars;

typedef struct s_token
{
	char			*cmdr;
	char			**arg;
	int	infile;
	int outfile;
	int	append;
	char	**delimiter;
	int				start_arg;
	int last_o;
	int last_i;
	char *envp[];
}					t_token;

typedef struct s_expand
{
	char *value;
	int v_len;
	int start;
	char *env;
	char e_len;
	
}				t_expand;

typedef struct s_wd
{
	char *pwd;
	char *oldpwd;
}				t_wd;

int					main(int ac, char **argv, char **envp);

// Syntax_Error 
int					have_digit(char *str, int i);
int					only_special(char *str);
int					no_authorize(char *str);
int					have_digit(char *str, int i);

// Expand
char				*checkdollars(char *str, char **envp);
char*	ft_dollars(char *str, char **envp, char *dest);
int dollars_in_quote(char *str, int index);
int	get_index(char *str);
char *change_value(char *env, char *str);
int	is_solo_dol(char *str, int index);

// List
void    list_am(t_token *token ,t_pars  **pars);
void	get_list(t_token *token, t_pars **pars);
void print_list(t_pars **pars);

// Utils
char				**ft_split(const char *s, char c);
int					ft_compare(char *str, char *str2, int size);
char				*ft_strnjoin(char *s1, char *s2, int c);
char	*malloc_cpy(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*strcpyn(char *dest, char *src, int index, int size);

// String_Check
int					check_start_end(char *str);
char				*ft_remove_quote(char *str);
int					check_quote(char *str, char *find);
int					check_in_quote(char *str, int index);
char	*add_space(char *str);
int	syntax_check(char *str);
char*	add_dquote(char *str);
int	check_pipe(char **cmd, char *str);

// Struct
int		init_struct(char **cmd, t_token *token, t_pars **pars);
int	init_token(char **cmd, t_token *token);

// Redirection
int    redirection(t_token *token, char **arg);
int nb_infile(t_token *token, char **arg);
int nb_outfile(t_token *token, char **arg);

// Free
int *ft_malloc(size_t size);
void    ft_free_list(t_pars **pars);

//Exec
char	*find_path(char **envp);
char	*get_right_cmd_path(char **paths, char *cmd);
void	free_tab(char **tab);
void	print_err(char *str);
void	check_status(int status);
void	child1(char *argv[], char *envp[], int *pipefd);
void	child2(char *argv[], char *envp[], int *pipefd);
void	exe_cmd(char **cmd_args, char **envp);

int		count_cmd(t_pars *pars);
int		executor(t_pars *pars, char ***envp, t_wd *wd);

//Array_utils
void	ft_free_double_array(char **to_free);
char**	ft_cpy_double_array(char **to_copy);
char	**ft_append_double_array(char **matrix, char *to_append);
char	**ft_pop_double_array(char **matrix, char *to_pop);
int		var_exists(char **envp, char *str);

//Export_utils

char	*remove_quotes(char *str, char c);
int	after_equal(char *str);
int	check_valid_identifier(char c);
int	var_already_exists(char *envp[], char *str);
int	check_param(char *str);

//Builtins

int	ft_pwd(void);
int	ft_exit(t_pars *pars, char **cmd, char **envp, t_wd *wd);
int	ft_export(char **cmd, char ***envp);
int	ft_echo(char **cmd);
int	ft_env(char *envp[]);
int	ft_unset(char **cmd, char ***envp);
int	ft_cd(char **cmd, char ***envp, t_wd *wd);

int	get_wds(t_wd *wd, char **envp);
#endif
