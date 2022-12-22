/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:37:56 by azari             #+#    #+#             */
/*   Updated: 2022/12/22 14:26:04 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_error(int tocheck)
{
	if (tocheck == -1)
	{
		perror(0);
		exit(0);
	}
}

char	**ft_split_mypath(char **env)
{
	int		i;
	char	*found;
	char	**found_splited;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i])
	{
		found = ft_substr(env[i], 5, ft_strlen(env[i]));
		found_splited = ft_split(found, ':');
		free(found);
		return (found_splited);
	}
	return (NULL);
}

char	*ft_check_mypath(char **cmd, char **env)
{
	char	*cmd_full_path;
	char	**path_list;
	char	*cmd_file;
	int		i;

	path_list = ft_split_mypath(env);
	if (!path_list)
	{
		perror("error");
		exit(1);
	}
	cmd_file = ft_strjoin("/", cmd[0]);
	i = -1;
	while (path_list[++i])
	{
		cmd_full_path = ft_strjoin(path_list[i], cmd_file);
		if (!access(cmd_full_path, F_OK | X_OK))
			return (ft_free(path_list), free(cmd_file), cmd_full_path);
		free(cmd_full_path);
		cmd_full_path = NULL;
	}
	perror("command not found");
	return (NULL);
}
