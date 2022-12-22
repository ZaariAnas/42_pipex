/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:29:53 by azari             #+#    #+#             */
/*   Updated: 2022/12/22 15:21:45 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int *fds, char **av, char **env)
{
	int		input;
	char	**cmd;
	char	*path;

	dup2(fds[1], 1);
	close(fds[0]);
	cmd = ft_split(av[2], ' ');
	path = ft_check_mypath(cmd, env);
	if (!path)
	{
		perror("path not found");
		exit(0);
	}
	input = open(av[1], O_RDONLY);
	if (input == -1)
	{
		perror ("pipex");
		exit(0);
	}
	dup2(input, 0);
	close(input);
	execve(path, cmd, env);
}

void	ft_second_child(int *fds, char **av, char **env)
{
	int		output;
	char	**cmd;
	char	*path;

	dup2(fds[0], 0);
	close(fds[1]);
	cmd = ft_split(av[3], ' ');
	path = ft_check_mypath(cmd, env);
	if (!path)
	{
		perror("path not found");
		exit(0);
	}
	output = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	output = -1;
	if (output == -1)
	{
		perror("pipex");
		exit(0);
	}
	dup2(output, 1);
	close(output);
	execve(path, cmd, env);
}

int	main(int ac, char *av[], char *env[])
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
	return (0);
}
