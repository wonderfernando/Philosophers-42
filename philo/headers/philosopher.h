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
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void ft_check_args_quant(int ac);
long	ft_atoi(const char *str);
int	ft_isdigit_str(char *str);
int	ft_isdigit(int c);
void    check_philo_number(char **str);
void check_valid_numbers(char **str);

typedef struct s_fork{
   int id;
   pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_philo {
   int id;
   pthread_t   thread;
   int count_mealded;
   t_fork *left_fork;
   t_fork *right_fork;
   t_data *data;
} t_philo;


typedef struct s_data {
   t_philo *philo;
   t_fork *fork;
   long  start_time;
   int   time_to_die;
   int   time_to_sleep;
   int   number_philos;
   int   time_to_eat;
   int   someone_died;
   int   number_must_eat;
} t_data;


