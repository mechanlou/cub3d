/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:30:35 by rkowalsk          #+#    #+#             */
/*   Updated: 2020/02/17 15:48:40 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_size(unsigned long n)
{
	long long int			size;

	size = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char		*ft_uitox_lowercase(unsigned long n)
{
	int			size;
	char		*str;
	int			i;
	char		*hextab;

	hextab = "0123456789abcdef";
	i = 0;
	size = get_size(n);
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[size--] = '\0';
	while (n)
	{
		str[size--] = hextab[n % 16];
		n /= 16;
	}
	return (str);
}

char		*ft_uitox_uppercase(unsigned long n)
{
	int			size;
	char		*str;
	int			i;
	char		*hextab;

	hextab = "0123456789ABCDEF";
	i = 0;
	size = get_size(n);
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[size--] = '\0';
	while (n)
	{
		str[size--] = hextab[n % 16];
		n /= 16;
	}
	return (str);
}
