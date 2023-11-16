/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:24:06 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 12:39:31 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wd	*init_wd(char **envp)
{
	t_wd	*new_wd;

	new_wd = malloc(sizeof(t_wd));
	if (!new_wd)
		return (NULL);
	get_wds(new_wd, envp);
	return (new_wd);
}

int	get_wds(t_wd *wd, char **envp)
{
	int	i;

	i = -1;
	wd->pwd = NULL;
	wd->oldpwd = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			wd->pwd = ft_substr(envp[i], 4, ft_strlen(envp[i]) - 4);
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			wd->oldpwd = ft_substr(envp[i], 7, ft_strlen(envp[i]) - 7);
	}
	if (wd->pwd == NULL)
		wd->pwd = getcwd(wd->pwd, 0);
	return (1);
}
