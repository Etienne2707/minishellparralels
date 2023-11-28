/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:50 by educlos           #+#    #+#             */
/*   Updated: 2023/11/28 12:49:10 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_red_quote(char *str)
{
	int i;
	int size;
	char *new;
	int k;

	size = ft_strlen(str);
	i = 1;
	k = 0;
	if (ft_strcmp(str, "\"<\"") == 0 || ft_strcmp(str, "\"<<\"") == 0
		|| ft_strcmp(str, "\">\"") == 0 || ft_strcmp(str, "\">>\"") == 0 ||
		ft_strcmp(str, "'<'") == 0 || ft_strcmp(str, "'<<'") == 0
		|| ft_strcmp(str, "'>'") == 0 || ft_strcmp(str, "'>>'") == 0)
	{
		printf("ouiiiiiii\n");
		new = malloc(sizeof(char) * size - 1);
		if (!new)
			return (NULL);
		while (i != size - 1)
			new[k++] = str[i++];
		new[k] = '\0';
		free(str);
		return (new);
	}
	return (str);
}

char	**put_arg_list2(char **dest, char **str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != 0)
	{
		if (ft_strcmp(">>", str[i]) == 0 || ft_strcmp("<<", str[i]) == 0
			|| ft_strcmp(">", str[i]) == 0 || ft_strcmp("<", str[i]) == 0)
			i = i + 2;
		if (str[i] != 0 && ft_strcmp(">>", str[i]) != 0 && ft_strcmp("<<",
				str[i]) != 0 && ft_strcmp(">", str[i]) != 0 && ft_strcmp("<",
				str[i]) != 0)
		{
			str[i] = remove_red_quote(str[i]);
			dest[c] = malloc_cpy(dest[c], str[i]);
			i++;
			c++;
		}
	}
	dest[c] = 0;
	return (dest);
}

char	**put_arg_list(char **dest, char **str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != 0)
	{
		if (ft_strcmp(">>", str[i]) == 0 || ft_strcmp("<<", str[i]) == 0
			|| ft_strcmp(">", str[i]) == 0 || ft_strcmp("<", str[i]) == 0)
				i = i + 2;
		if (str[i] != 0 && ft_strcmp(">>", str[i]) != 0 && ft_strcmp("<<",
				str[i]) != 0 && ft_strcmp(">", str[i]) != 0 && ft_strcmp("<",
				str[i]) != 0)
		{
			i++;
			c++;
		}
	}
	dest = malloc(sizeof(char *) * (c + 1));
	if (!dest)
		return (NULL);
	dest = put_arg_list2(dest, str);
	return (dest);
}

static t_pars	*get_info(t_token *token)
{
	t_pars	*new;

	new = (t_pars *)malloc(sizeof(t_pars));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->cmd = put_arg_list(new->cmd, token->arg);
	new->delimiter = ft_cpy_double_array(token->delimiter);
	new->outfile = token->outfile;
	new->infile = token->infile;
	new->next = NULL;
	new->prev = NULL;
	new->token = token;
	return (new);
}

void	lst_add_back(t_pars **pars, t_pars *new)
{
	t_pars	*tmp;

	tmp = *pars;
	if (*pars == NULL)
	{
		*pars = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	get_list(t_token *token, t_pars **pars)
{
	t_pars	*tmp;

	tmp = get_info(token);
	if (!tmp)
		return ;
	lst_add_back(pars, tmp);
}
