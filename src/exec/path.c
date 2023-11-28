/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:54:48 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/28 19:46:32 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*get_right_cmd_path(char **paths, char *cmd)
{
	char	*temp;
	char	*cmd_path;

	while (paths && *paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (cmd_path != NULL)
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}
