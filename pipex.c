/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:29:53 by azari             #+#    #+#             */
/*   Updated: 2022/12/21 17:45:12 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char**	ft_split_mypath(char** env)
{
	int i;
	char* found;
	char** found_splited;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i])
	{
		found = ft_substr(env[i], 5, ft_strlen(env[i]));
		found_splited = ft_split(found , ':');
		free(found);
		return (found_splited);
	}
	return (NULL);
}

void	ft_free(char **str)
{
	int i;

	i = -1;	
	while(str[++i])
		free(str[i]);
	free(str);
}

char	*ft_check_mypath(char **cmd, char **env)
{
	char	*cmd_full_path;
	char	**path_list;
	char	*cmd_file;
	int		i;

	path_list = ft_split_mypath(env);
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


void	ft_first_child(int* fds, char **av, char** env)
{
	int		input;
	char**	cmd;
	char*	path;

	dup2(fds[1], 1);
	close(fds[0]);
	cmd = ft_split(av[2], ' ');
	path = ft_check_mypath(cmd, env);
	input = open(av[1], O_RDONLY);
	dup2(input, 0);
	execve(path, cmd, env);
}

void	ft_second_child(int* fds, char **av, char** env)
{
	int		output;
	char**	cmd;
	char*	path;

	dup2(fds[0], 0);
	close(fds[1]);
	cmd = ft_split(av[3], ' ');
	path = ft_check_mypath(cmd, env);
	output = open(av[4], O_CREAT | O_RDWR, 0777);
	dup2(output, 1);
	execve(path, cmd, env);
}

int main(int ac, char* av[], char* env[])
{
	pid_t	pid[2];
	int		fds[2];
	int		check;

	if (ac != 5)
	{
		write(2, "unvalid number of arguments !\n", 31);
		exit(0);
	}
	check = pipe(fds);
	ft_check_error(check);
	pid[0] = fork();
	ft_check_error(pid[0]);
	if (!pid[0])
		ft_first_child(fds, av, env);
	else
	{
		wait(NULL);
		ft_second_child(fds, av, env);
		close(fds[0]);
		close(fds[1]);
	}
}
