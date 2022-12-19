/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:01:07 by azari             #+#    #+#             */
/*   Updated: 2022/12/19 11:06:40 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *dst, const char *src, size_t n)
{
	size_t	i;

	if (n <= 0)
		return (0);
	i = 0;
	while (dst[i] == src[i] && (dst[i] || src[i]) && i < n - 1)
	i++;
	return ((unsigned char)dst[i] - (unsigned char)src[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s + start);
	i = 0;
	if (len > slen)
		len = slen;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	slen = ft_strlen(s);
	i = -1;
	while (++i < len && start[s] && start < slen)
		*(str + i) = *(s + start + i);
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (++i < len1)
		ptr[i] = s1[i];
	while (j < len2)
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	i;

	i = -1;
	ptr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (++i < ft_strlen(str))
		ptr[i] = str[i];
	ptr[i] = '\0';
	return (ptr);
}