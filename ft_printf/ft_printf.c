/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:18:11 by ferda-si          #+#    #+#             */
/*   Updated: 2024/05/29 14:18:16 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putchar_i(char c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_print_str(const char *s, int i)
{
	if (!s)
	{
		write(1, "(null)", 6);
		i += 6;
	}
	else
	{
		while (*s)
		{
			i = ft_putchar_i(*s, i);
			s++;
		}
	}
	return (i);
}

int	ft_print_dec(const char *str, int j, int i, va_list args)
{
	if (str[j] == 's')
		i = ft_print_str(va_arg(args, char *), i);
	if (str[j] == 'c')
		i = ft_putchar_i(va_arg(args, int), i);
	if (str[j] == 'p')
		i = ft_print_memory(va_arg(args, unsigned long long), i);
	if (str[j] == 'd' || str[j] == 'i')
		i = ft_print_d(va_arg(args, int), i);
	if (str[j] == 'X')
		i = ft_print_x(va_arg(args, unsigned int), i, 1);
	if (str[j] == 'x')
		i = ft_print_x(va_arg(args, unsigned int), i, 0);
	if (str[j] == 'u')
		i = ft_print_u(va_arg(args, unsigned int), i);
	if (str[j] == '%')
		i = ft_putchar_i('%', i);
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		j;
	va_list	args;

	j = 0;
	i = 0;
	va_start(args, str);
	while (str[j])
	{
		if (str[j] == '%')
			i = ft_print_dec(str, ++j, i, args);
		else
		{
			i = ft_putchar_i(str[j], i);
		}
		j++;
	}
	return (i);
}
