/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:13:14 by educlos           #+#    #+#             */
/*   Updated: 2023/11/13 19:55:26 by mle-duc          ###   ########.fr       */
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
	redirection(token, token->arg);
	i = 0;
	while (token->arg[i] != 0)
	{
		token->arg[i] = ft_remove_quote(token->arg[i]);
		i++;
	}
	free(temp);
	return (token->arg);
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
	//print_list(pars);
	return (1);
}
