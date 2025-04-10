#include "philosopher.h"

typedef struct philo {
   int count_mealded;
} s_philo;

typedef struct t_data {
   s_philo *philo;
} s_data;

s_data *get_data ()
{
   static s_data *data_str = NULL;
   if (data_str == NULL)
      data_str = (s_data*) malloc(sizeof(s_data));
   return (data_str);
}

void philopher_doing_thins()
{
   printf("%d\n",get_data()->philo->count_mealded);
}

int main(int ac, char **av)
{
   s_philo *philo = NULL;
   philo = (s_philo*)malloc(sizeof(s_philo));
   philo->count_mealded = 42;
   get_data()->philo = philo;
   philopher_doing_thins();
   exit(0);
   ft_check_args_quant(ac);
   check_valid_numbers(av);
   check_philo_number(av);

}