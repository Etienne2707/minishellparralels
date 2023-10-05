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

	i = token->start_arg;
	temp = (ft_strnrcpy(cmd, temp, i));
	token->arg = ft_split(temp, ' ');
	i = 0;
	while (token->arg[i] != 0)
	{
		token->arg[i] = ft_remove_quote(token->arg[i], 34);
		i++;
	}
	return (token->arg);
}

char	*get_cmdr(char *cmd, t_token *token)
{
	int		i;
	int		c;
	int		k;
	char	*str;

	i = 0;
	c = 0;
	token->start_arg = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] != 34 && cmd[i] != 39 && cmd[i] != '<' && cmd[i] != '>'
			&& cmd[i] != '-' && (cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < '0'
				|| cmd[i] > '9'))
		{
			return (NULL);
		}
		k = i;
		while (cmd[i + c] != '\0' && cmd[i + c] != ' ' || (cmd[i + c] >= 'a'
				&& cmd[i + c] <= 'z'))
            {
                //printf("valeur de retour %d && %d\n", check_in_quote(cmd, i + c), cmd[i+c]);
                //if (cmd[i + c] == ' ' && check_in_quote(cmd, i + c) == -1)
                c++;
            }
			
		break ;
	}
	i = 0;
	printf("valeur : %d\n", c);
	str = malloc(sizeof(char) * c + 1);
	while (i < c)
		str[i++] = cmd[k++];
	str[i] = '\0';
    str = ft_remove_quote(str, 0);
    printf("%s\n", str);
	token->start_arg = k;
	return (str);
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
		token[i].cmdr = get_cmdr(cmd[i], &token[i]);
		token[i].arg = get_arg(cmd[i], &token[i]);
		i++;
	}
	k = 0;
	i = 0;
	while (cmd[i] != 0)
	{
		printf("cmd[%d] = %s\n", i, token[i].cmdr);
		k = 0;
		while (token[i].arg[k] != 0)
		{
			printf("arg = %s\n", token[i].arg[k]);
			k++;
		}
		i++;
	}
	return (1);
}

int	token(char **cmd, t_token *token)
{
	init_struct(cmd, token);
	int i;
	int k;
	int c;

	return (1);
}