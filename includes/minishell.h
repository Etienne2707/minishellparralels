/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:48:24 by educlos           #+#    #+#             */
/*   Updated: 2023/10/20 02:51:58 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include<readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


typedef struct s_pars
{
	char	**cmd;
	int	infile;
	int outfile;
	int	append;
	char	**delimiter;
	struct s_pars	*next;
	struct s_pars	*prev;
	  
}					t_pars;


enum				e_token
{
	CMD,
	ARG,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_DINPUT,
	R_DOUTPUT,
	REDIRECT_TMP
};

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
}					t_token;

typedef struct s_expand
{
	char *value;
	int v_len;
	int start;
	char *env;
	char e_len;
	
}				t_expand;

typedef struct s_malloc
{
    void *allocation;
    struct s_malloc *next;
} 			t_malloc;




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


// List
void    list_am(t_token *token ,t_pars  **pars);
void	get_list(t_token *token, t_pars **pars);
void print_list(t_pars **pars);


// Utils
char				*ft_strlcpy(char *dest, char *src, unsigned int size);
char				**ft_split(const char *s, char c);
int					ft_strlen(char *str);
int					ft_compare(char *str, char *str2, int size);
char				*ft_strlcpy(char *dest, char *src, unsigned int size);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnjoin(char *s1, char *s2, int c);
int	ft_strcmp(char *s1, char *s2);
char	*malloc_cpy(char *dest, char *src);
char *ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*strcpyn(char *dest, char *src, int index, int size);


// String_Check
int					check_start_end(char *str);
char				*ft_remove_quote(char *str);
int					check_quote(char *str, char *find);
int					check_in_quote(char *str, int index);
char    *add_space(char *str);
int syntax_check(char *str);
char*	add_dquote(char *str);
int	check_pipe(char **cmd, char *str);


// Struct
int					init_struct(char **cmd, t_token *token, t_pars **pars);
int	init_token(char **cmd, t_token *token);
void    free_token(t_token **token, int i);



// Redirection
int    redirection(t_token *token, char **arg);
int nb_infile(t_token *token, char **arg);
int nb_outfile(t_token *token, char **arg);


// Free
int *ft_malloc(size_t size);
void    ft_free_list(t_pars **pars);

#endif
