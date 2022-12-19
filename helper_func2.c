/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:37:56 by azari             #+#    #+#             */
/*   Updated: 2022/12/19 11:41:21 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_check_error(int tocheck, int checker)
{
	if(checker == -1 && checker == -1)
	{
		perror(0);
		exit(0);
	}
	else if (checker != tocheck)
	{
		perror(0);
		exit(0);
	}
}