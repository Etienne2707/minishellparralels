/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:24:06 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 08:45:55 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_wds(t_wd *wd, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			wd->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			wd->oldpwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
	}
	return (1);
}
