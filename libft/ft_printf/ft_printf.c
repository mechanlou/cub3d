/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:33:52 by rkowalsk          #+#    #+#             */
/*   Updated: 2020/03/02 17:24:37 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	printing(va_list params, const char *str, size_t i)
{
	int		size;
	t_flag	flags;
	int		ret;

	size = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			flags = ft_pars_flags(params, (char *)str + ++i);
			if (flags.error || (ret = ft_print_param(params, flags)) == -1)
				return (-1);
			size += ret;
			while (ft_conv_or_flag(str[i]) != 1)
				i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			size++;
		}
		i++;
	}
	return (size);
}

int			ft_printf(const char *str, ...)
{
	va_list params;
	int		size;
	size_t	i;

	i = 0;
	va_start(params, str);
	size = printing(params, str, i);
	va_end(params);
	return (size);
}
