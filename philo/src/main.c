#include "philosopher.h"






t_data *get_data ()
{
   static t_data *data_str = NULL;
   if (data_str == NULL)
      data_str = (t_data*) malloc(sizeof(t_data));
   return (data_str);
}

void philopher_doing_thins()
{
   printf("%d\n",get_data()->philo->count_mealded);
}


void init_forks(t_data *data){
   int	i;
   t_fork	*fork;

   fork = (t_fork*)malloc(sizeof(t_fork) * data->number_philos);
   i = 0;
   while (i < data->number_philos)
   {
		fork[i].id = i+1;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
   }
   data->fork = fork;
}


void init_philos(t_data *data){
   int	i;
   t_philo	*philo;

   philo = (t_philo*)malloc(sizeof(t_philo) * data->number_philos);
   i = 0;
   while (i < data->number_philos)
   {
		philo[i].id = i+1;
		philo[i].left_fork = &data->fork[i];
		philo[i].right_fork = &data->fork[(i + 1) % data->number_philos];
		philo[i].data = data;
		i++;
   }
   data->philo = philo;
}

void print_forks(t_data data)
{
	for (int i = 0; i < data.number_philos; i++)
	{
		printf("fork %d \n", data.fork[i].id);
	}
}

void print_philos(t_data data)
{
	for (int i = 0; i < data.number_philos; i++)
	{
		printf("philo %d \n", data.philo[i].id);
	}
}

void routine_philosopher()
{

}


int main(int ac, char **av)
{
  // t_philo *philo = NULL;
   t_data data;
   init_forks(&data);
   init_philos(&data);
   //routine
   //monitoring
	exit(0);

   ft_check_args_quant(ac);
   check_valid_numbers(av);
   check_philo_number(av);

}