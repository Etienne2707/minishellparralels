/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:13:14 by educlos           #+#    #+#             */
/*   Updated: 2023/11/28 19:47:42 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

char	*ft_strnrcpy(char *str, char *temp, int c)
{
	int		i;
	char	tmp;

	temp = malloc(sizeof(char) * ft_strlen(str) - c + 1);
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
	temp = NULL;
	temp = (ft_strnrcpy(cmd, temp, i));
	token->arg = ft_split(temp, ' ');
	i = 0;
	while (token->arg[i] != 0)
	{
		if (ft_strcmp(token->arg[i], "\"\"") == 0 && token->arg[i + 1] == NULL)
			token->arg[i] = ft_remove_quote3(token->arg[i]);
		else if (ft_strcmp(token->arg[i], "\'\'") == 0
			&& token->arg[i + 1] == NULL)
			token->arg[i] = ft_remove_quote3(token->arg[i]);
		else
			token->arg[i] = ft_remove_quote(token->arg[i]);
		i++;
	}
	redirection(token, token->arg);
	free(temp);
	return (token->arg);
}

static void	free_token(t_token **token, int i)
{
	int	j;
	int	k;

	j = 0;
	while (j < i)
	{
		k = 0;
		while ((*token)[j].arg[k])
			free((*token)[j].arg[k++]);
		free((*token)[j].arg);
		free((*token)[j].delimiter);
		j++;
	}
	free(*token);
}

int	init_struct(char **cmd, t_token *token, t_pars **pars)
{
	int	i;

	i = 0;
	while (cmd[i] != 0)
		i++;
	token = malloc(sizeof(t_token) * i);
	if (!token)
		return (0);
	i = 0;
	while (cmd[i] != 0)
	{
		token[i].arg = get_arg(cmd[i], &token[i]);
		get_list(&token[i], pars);
		i++;
	}
	free_token(&token, i);
	return (1);
}
