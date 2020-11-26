/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_params_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:21:30 by rkowalsk          #+#    #+#             */
/*   Updated: 2020/02/18 16:04:35 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static char	*get_precision(char *str, t_flag flags)
{
	int		i;
	int		j;
	char	*prec;

	i = ft_strlen(str);
	if (!flags.precision || flags.nb_precisions <= i)
		i = 0;
	else
		i = flags.nb_precisions - i;
	if (!(prec = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	prec[i] = '\0';
	j = 0;
	while (j < i)
		prec[j++] = '0';
	return (prec);
}

static char	*get_width(char *str, char *prec, t_flag flags, bool neg)
{
	int		i;
	int		j;
	char	*width;
	char	c;

	c = ' ';
	if (flags.zero)
		c = '0';
	i = ft_strlen(str) + ft_strlen(prec) + neg;
	if (flags.nb_width <= i)
		i = 0;
	else
		i = flags.nb_width - i;
	if (!(width = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	width[i] = '\0';
	j = 0;
	while (j < i)
		width[j++] = c;
	return (width);
}

static void	print_all(t_flag flags, bool neg, char *width, char *prec)
{
	if (!flags.minus)
	{
		if (neg && flags.zero)
			ft_putchar_fd('-', 1);
		ft_putstr_fd(width, 1);
		if (neg && !flags.zero)
			ft_putchar_fd('-', 1);
	}
	else if (neg)
		ft_putchar_fd('-', 1);
	ft_putstr_fd(prec, 1);
}

static void	check_weird_case(t_flag flags, char *str)
{
	if (str[0] == '0' && flags.precision && !flags.nb_precisions)
		str[0] = '\0';
}

int			ft_print_di(va_list params, t_flag flags)
{
	char	*str;
	char	*prec;
	char	*width;
	long	size;
	bool	neg;

	neg = false;
	if (!(str = ft_itoa(va_arg(params, int))))
		return (-1);
	if (str[0] == '-')
		neg = true;
	check_weird_case(flags, str + neg);
	if (!(prec = get_precision(str + neg, flags)))
		return (ft_free_all(1, str));
	if (!(width = get_width(str + neg, prec, flags, neg)))
		return (ft_free_all(2, prec, str));
	print_all(flags, neg, width, prec);
	ft_putstr_fd(str + neg, 1);
	if (flags.minus)
		ft_putstr_fd(width, 1);
	size = ft_strlen(str) + ft_strlen(prec) + ft_strlen(width);
	ft_free_all(3, width, prec, str);
	return (size);
}
