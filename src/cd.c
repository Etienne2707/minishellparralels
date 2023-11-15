/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:40:53 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 08:44:09 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path(char **envp, char *path_to_find)
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
		ft_putstr_fd(" not set", 2);
	}
	return (path);
}

static void	err_msg(char **cmd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" aucun fichier ou dossier de ce type\n", 2);
}

static void	refresh_wd(t_wd *wd)
{
	char	*tmp;

	tmp = ft_strdup(wd->pwd);
	free(wd->oldpwd);
	wd->oldpwd = tmp;
	free(wd->pwd);
	wd->pwd = NULL;
	wd->pwd = getcwd(wd->pwd, 0);
}

static void	refresh_env(t_wd *wd, char ***envp)
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

int	ft_cd(char **cmd, char ***envp, t_wd *wd)
{
	int	path;

	if (!cmd[1])
		path = get_path(*envp, "HOME=");
	else if (cmd[1][0] == '-' && cmd[1][1] == 0)
		path = get_path(*envp, "OLDPWD=");
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: too much arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else
	{
		path = chdir(cmd[1]);
		if (path)
			err_msg(cmd);
	}
	if (path)
		return (EXIT_FAILURE);
	refresh_wd(wd);
	refresh_env(wd, envp);
	return (EXIT_SUCCESS);
}
