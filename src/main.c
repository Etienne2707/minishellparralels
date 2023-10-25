#include "minishell.h"

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
	printf("%s\n", dest);
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
	return (1);	
}


int	check_str(char *str, t_token *token, char **envp, t_pars **pars)
{

    if ((Syntax_Error(str, token, envp, pars)) == -1)
	{
		write(1, "Syntax Error\n", 13);
		return (-1);
	}
	return (1);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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
		add_history(str);
		check_str(str, token, envp, &pars);
		if (ft_strcmp(str, "exit") == 0)
		{
			free(str);
			return (0);
		}
		ft_free_list(&pars);
		pars = NULL;
		str = readline("Minishell > ");
	}
	return (1);
}