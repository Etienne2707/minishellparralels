/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:33 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/28 13:04:11 by mle-duc          ###   ########.fr       */
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
