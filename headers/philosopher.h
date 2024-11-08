/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:54:04 by ferda-si          #+#    #+#             */
/*   Updated: 2024/11/08 17:54:18 by ferda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_check_args_quant(int ac);
long	ft_atoi(const char *str);
int	ft_isdigit_str(char *str);
int	ft_isdigit(int c);
void    check_philo_number(char **str);
void check_valid_numbers(char **str);