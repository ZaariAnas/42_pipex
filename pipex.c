/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:29:53 by azari             #+#    #+#             */
/*   Updated: 2022/12/21 13:33:53 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char**	ft_split_mypath(char** env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(ft_substr(env[i], 5, ft_strlen(env[i])),':'));
		i++;
	}
	return (NULL);
}

char*	ft_check_mypath(char** cmd, char** env)
{
	char**	path_list;
	char*	cmd_file;
	int		i;

	i = -1;
	path_list = ft_split_mypath(env);
	if (!path_list)
	{
		printf("shit happenned here !\n");
		free(path_list);
		return(NULL);
	}
	while (path_list[++i])
	{
		cmd_file = ft_strjoin(path_list[i], ft_strjoin("/", cmd[0]));
		if(!cmd_file)
		{
			free(cmd_file);
			return (NULL);
		}
		if (!access(cmd_file, R_OK))
		{
			free (path_list);
			return (cmd_file);
		}
	}
	free (cmd_file);
	free (path_list);
	return (NULL);
}

void	ft_first_child(int* fds, char **av, char** env)
{
	int		input;
	char**	cmd;
	char*	path;

	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
	cmd = ft_split(av[2], ' ');
	path = ft_check_mypath(av, env);
	input = open(av[1], O_RDONLY);
	dup2(input, 0);
	// close(input);
	execve(path, cmd, env);
}

void	ft_second_child(int* fds, char **av, char** env)
{
	int		output;
	char**	cmd;
	char*	path;

	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	cmd = ft_split(av[3], ' ');
	path = ft_check_mypath(cmd, env);
	output = open(av[4], O_CREAT | O_RDWR, 0777);
	dup2(output, 1);
	// close(output);
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
	pid[1] = fork();
	ft_check_error(pid[1]);
	if (!pid[1])
		ft_second_child(fds, av, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
