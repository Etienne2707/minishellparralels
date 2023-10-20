#include "minishell.h"


int	check_pipe(char **cmd, char *str)
{
	int i;
	int k;
	int c;

	i = 0;
	c = 0;
	if (check_start_end(str) == -1)
		return (-1);
	while(cmd[i] != 0)
	{
		k = 0;
		c = 0;
		while (cmd[i][k] != '\0')
		{
			if (cmd[i][k] != ' ')
				c++;
			k++;
			
		}
		if (c == 0)
				return (-1);
		i++;
	}
	return (1);
	
}

int	Syntax_Error(char *str, t_token *token, char **envp, t_pars **pars)
{
	int	i;
	char **cmd;
	char *dest;

	i = 0;
	if (syntax_check(str) == 0)
			return (-1);
	dest = malloc_cpy(dest,str);
	dest = ft_dollars(dest, envp, dest);
	dest = add_space(dest);
	cmd = ft_split(dest, '|');
	if ((check_pipe(cmd, dest)) == -1)
		return (-1);
	free(dest);
	init_struct(cmd, token, pars);
	while (cmd[i] != 0)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	//get_list(cmd,token);
	return (1);
	
}


int	check_str(char *str, t_token *token, char **envp, t_pars **pars)
{

	//list_am(token,pars);
    if ((Syntax_Error(str, token, envp, pars)) == -1)
	{
		write(1, "Syntax Error\n", 13);
		return (-1);
	}
	return (1);
}

void	free_all(t_token *token, char *str)
{
	free(str);
	int i;

	i = 0;
	while (token->cmdr[i] != 0)
		free(token->cmdr[i++]);
}

int	main(int ac, char **argv, char **envp)
{
	t_token *token;
	t_pars	*pars;
	(void)ac;
	(void)argv;
	int i;
	char *str;

	str = NULL;
	pars = NULL;
	str = readline("Minishell > ");
	while (-1)
	{
		//printf("%s\n", str);
		add_history(str);
		check_str(str, token, envp, &pars);
		if (strcmp(str, "exit") == 0)
		{
			free(str);
			return (0);
		}
		str = readline("Minishell > ");
	}
	return (1);
}