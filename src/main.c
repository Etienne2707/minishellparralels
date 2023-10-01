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

int	Syntax_Error(char *str, t_token *token, char **envp)
{
	int	i;
	char **cmd;

	i = 0;
	str = checkdollars(str, envp);
	printf("je suis %s\n", str);
	cmd = ft_split(str, '|');	
	if ((check_pipe(cmd, str)) == -1)
		return (-1);
	if ((no_authorize(str)) == -1)
		return (-1);
	init_struct(cmd, token);
	return (1);
	
}
int	check_str(char *str, t_token *token, char **envp)
{

    if ((Syntax_Error(str, token, envp)) == -1)
	{
		write(1, "Syntax Error\n", 13);
		return (-1);
	}
	return (1);
}

int	main(int ac, char **argv, char **envp)
{
	t_token *token;
	(void)ac;
	(void)argv;
	int i;
	char *str;

	token = NULL;
	str = NULL;
	str = readline("Minishell > ");
	while (-1)
	{
		//printf("%s\n", str);
		check_str(str, token, envp);
		if (strcmp(str, "exit") == 0)
			return (0);
		str = readline("Minishell > ");
	}
	return (1);
}