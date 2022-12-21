/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:54:50 by azari             #+#    #+#             */
/*   Updated: 2022/12/21 12:16:13 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

void	ft_check_error(int tocheck);
char*	ft_check_mypath(char** cmd, char** env);
char	**ft_split(const char *s, char c);
char**	ft_split_mypath(char** env);
size_t	ft_strlen(const char *str);
void	ft_first_child(int* fds, char **av, char** env);
void	ft_second_child(int* fds, char **av, char** env);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);

#endif