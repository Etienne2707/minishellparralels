/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:33 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/28 16:56:20 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
}

static void	print_great_less_error(int n, char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (c == '<')
	{
		if (n < 4)
			ft_putstr_fd("`newline'\n", 2);
		else if (n == 4)
			ft_putstr_fd("`<'\n", 2);
		else if (n == 5)
			ft_putstr_fd("`<<'\n", 2);
		else if (n > 5)
			ft_putstr_fd("`<<<'\n", 2);
	}
	else if (c == '>')
	{
		if (n < 3)
			ft_putstr_fd("`newline'\n", 2);
		else if (n == 3)
			ft_putstr_fd("`>'\n", 2);
		else if (n > 3)
			ft_putstr_fd("`>>'\n", 2);
	}
}

void	less_great_error(char *str)
{
	int	i;
	int	less;
	int	great;

	i = -1;
	less = 0;
	great = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			great++;
		if (str[i] == '<')
			less++;
	}
	if (less > great)
		print_great_less_error(less, '<');
	else if (less <= great)
		print_great_less_error(great, '>');
}

int	ft_check_red_with_quotes(char *str)
{
	if (ft_strcmp(str, "\"<\"") == 0 || ft_strcmp(str, "\"<<\"") == 0
		|| ft_strcmp(str, "\">\"") == 0 || ft_strcmp(str, "\">>\"") == 0
		|| ft_strcmp(str, "'<'") == 0 || ft_strcmp(str, "'<<'") == 0
		|| ft_strcmp(str, "'>'") == 0 || ft_strcmp(str, "'>>'") == 0)
		return (1);
	else
		return (0);
}

char	*remove_red_quote(char *str)
{
	int		i;
	int		size;
	char	*new;
	int		k;

	size = ft_strlen(str);
	i = 1;
	k = 0;
	if (ft_check_red_with_quotes(str))
	{
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
