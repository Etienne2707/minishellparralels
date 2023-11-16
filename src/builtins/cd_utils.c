/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:40:53 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 12:44:11 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path(char **envp, char *path_to_find)
{
	char	*tmp;
	int		i;
	int		path;

	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], path_to_find, ft_strlen(path_to_find)) == 0)
			tmp = ft_substr(envp[i], ft_strlen(path_to_find),
					ft_strlen(envp[i]) - ft_strlen(path_to_find));
		i++;
	}
	path = chdir(tmp);
	free(tmp);
	if (path)
	{
		path_to_find = ft_substr(path_to_find, 0, ft_strlen(path_to_find) - 1);
		ft_putstr_fd(path_to_find, 2);
		free(path_to_find);
		ft_putstr_fd(" not set\n", 2);
	}
	return (path);
}

int	oldpwd_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	refresh_wd(t_wd *wd, char ***envp)
{
	char	*tmp;
	char	**tmp2;

	tmp = NULL;
	if (wd->pwd)
		tmp = ft_strdup(wd->pwd);
	if (wd->oldpwd == NULL || !oldpwd_exists(*envp))
	{
		wd->oldpwd = tmp;
		if (wd->oldpwd)
		{
			tmp = ft_strjoin("OLDPWD=", tmp);
			tmp2 = ft_append_double_array(*envp, tmp);
			ft_free_double_array(*envp);
			*envp = tmp2;
		}
	}
	else
	{
		free(wd->oldpwd);
		wd->oldpwd = tmp;
	}
	free(wd->pwd);
	wd->pwd = NULL;
	wd->pwd = getcwd(wd->pwd, 0);
}

void	refresh_env(t_wd *wd, char ***envp)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD=", 7) == 0)
		{
			tmp = ft_strjoin("OLDPWD=", wd->oldpwd);
			free((*envp)[i]);
			(*envp)[i] = tmp;
		}
		else if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
		{
			tmp = ft_strjoin("PWD=", wd->pwd);
			free((*envp)[i]);
			(*envp)[i] = tmp;
		}
		i++;
	}
}
