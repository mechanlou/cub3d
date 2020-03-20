/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:35:05 by rkowalsk          #+#    #+#             */
/*   Updated: 2020/02/17 15:56:01 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char *str, char c)
{
	int	size;

	size = 0;
	while (str[size] && str[size != c])
		size++;
	return (size);
}

static int	get_nb_str(const char *str, char c)
{
	int i;
	int	nb;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			nb++;
		i++;
	}
	return (nb);
}

static char	*filloc_str(char *s, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * get_size((char *)s, c) + 1)))
		return (NULL);
	while (s[i] != c && s[i] != '\0')
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

static char	**free_all(char **strs, int j)
{
	--j;
	while (j > 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (!(strs = (char **)malloc((get_nb_str(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			if ((strs[j] = filloc_str((char *)s + i, c)) == NULL)
				return (free_all(strs, j));
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	strs[j] = NULL;
	return (strs);
}
