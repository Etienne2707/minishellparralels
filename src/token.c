#include "minishell.h"

char	*ft_strnrcpy(char *str, char *temp, int c)
{
	int		i;
	char	tmp;

	temp = malloc(sizeof(char) * strlen(str) - c + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[c] != '\0')
	{
		tmp = str[c];
		temp[i] = tmp;
		i++;
		c++;
	}
	temp[i] = '\0';
	return (temp);
}

	char	**get_arg(char *cmd, t_token *token)
	{
		int		i;
		char	*temp;

		i = 0;
		temp = (ft_strnrcpy(cmd, temp, i));
		token->arg = ft_split(temp, ' ');
		redirection(token, token->arg);
		i = 0;
		while (token->arg[i] != 0)
		{
			token->arg[i] = ft_remove_quote(token->arg[i], 34);
			i++;
		}
		free(temp);
		return (token->arg);
	}


	int	init_struct(char **cmd, t_token *token)
	{
		int	i;
		int	k;

		i = 0;
		while (cmd[i] != 0)
			i++;
		k = i;
		token = malloc(sizeof(t_token) * i);
		if (!token)
			return (0);
		i = 0;
		while (cmd[i] != 0)
		{
			token[i].arg = get_arg(cmd[i], &token[i]);
			i++;
		}
		k = 0;
		i = 0;
		while (cmd[i] != 0)
		{
			printf("cmd[%d]\n", i);
			k = 0;
			while (token[i].arg[k] != 0)
			{
				printf("arg = %s\n", token[i].arg[k]);
				k++;
			}
			printf("outfile : %d\n", token[i].outfile);
			printf("infile : %d\n", token[i].infile);
			printf("append : %d\n", token[i].append);
			k = 0;
			if (token[i].delimiter != NULL)
				while (token[i].delimiter[k] != 0)
				{
					printf("heredoc[%d] : %s \n", k,token[i].delimiter[k]);
					k++;
				}
			i++;
		}
		return (1);
	}

int	token(char **cmd, t_token *token)
{
	init_struct(cmd, token);
	return (1);
}