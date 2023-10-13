/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:48:24 by educlos           #+#    #+#             */
/*   Updated: 2023/10/13 18:33:12 by educlos          ###   ########.fr       */
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


int					main(int ac, char **argv, char **envp);
int					have_digit(char *str, int i);
int					check_start_end(char *str);
int					only_special(char *str);
int					no_authorize(char *str);
char				**ft_split(const char *s, char c);
int					init_struct(char **cmd, t_token *token);
int					ft_strlen(char *str);
int					ft_compare(char *str, char *str2, int size);
char				*ft_strlcpy(char *dest, char *src, unsigned int size);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strnjoin(char *s1, char *s2, int c);
char				*checkdollars(char *str, char **envp);
int					check_quote(char *str, char *find);
char				*ft_remove_quote(char *str);
int					check_in_quote(char *str, int index);
void    list_am(t_token *token ,t_pars  **pars);
int    redirection(t_token *token, char **arg);
int	get_list(char **cmd, t_token *token);
char    *add_space(char *str);
int	init_token(char **cmd, t_token *token);
int syntax_check(char *str);
int	get_list(char **cmd, t_token *token);
#endif
