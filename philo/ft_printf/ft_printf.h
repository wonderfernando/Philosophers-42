/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:19:11 by ferda-si          #+#    #+#             */
/*   Updated: 2024/05/29 14:19:17 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

int	ft_printf(const char *formato, ...);
int	ft_print_dec(const char *formato, int j, int i, va_list args);
int	ft_print_d(int nb, int i);
int	ft_print_u(unsigned int nb, int i);
int	ft_print_memory(uintptr_t u, int i);
int	ft_print_hex(uintptr_t u, int i);
int	ft_print_x(unsigned int nb, int i, int dec);
int	ft_print_str(const char *s, int i);
int	ft_putchar_i(char c, int i);

#endif
