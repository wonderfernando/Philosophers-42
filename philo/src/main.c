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

long long get_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
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
		philo[i].last_meal = data->start_time;
		philo[i].data = data;
		i++;
   }
   data->philo = philo;
}
 
void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	printf("timestamp_in_ms %d has taken a fork \n", philo->id);
	pthread_mutex_lock(&philo->right_fork->mutex);	
	printf("timestamp_in_ms %d has taken a fork \n", philo->id);
	printf("timestamp_in_ms %d is eating \n", philo->id);
	usleep(300000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
void *routine_philosopher(void* dt)
{
	t_philo *philo;

	philo = (t_philo*) dt;
	eat(philo);
	//usleep(400000);
	return NULL;
}

void  start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, routine_philosopher, &data->philo[i]);
		i++;
	}
}

void waintg_threads(t_data *data)
{
   int   i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
/* number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
 */
void	init_data(t_data *data, int ac, char **av)
{
	data->number_philos = ft_atoi(av[1]);
	data->time_to_die =  ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_must_eat = ft_atoi(av[5]);
	else
		data->number_must_eat = -1;
	data->start_time = get_time_ms();
}

int main(int ac, char **av)
{
  // t_philo *philo = NULL;
   t_data data;
   init_data(&data, ac, av);
   init_forks(&data);
   init_philos(&data);
   start_simulation(&data);
   waintg_threads(&data);
   //routine
   //monitoring
	exit(0);
   ft_check_args_quant(ac);
   check_valid_numbers(av);
   check_philo_number(av);

}