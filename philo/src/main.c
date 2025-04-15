#include "philosopher.h"

t_data *get_data()
{
	static t_data *data_str = NULL;
	if (data_str == NULL)
		data_str = (t_data *)malloc(sizeof(t_data));
	return (data_str);
}

long long get_current_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void init_forks(t_data *data)
{
	int i;
	t_fork *fork;

	fork = (t_fork *)malloc(sizeof(t_fork) * data->number_philos);
	i = 0;
	while (i < data->number_philos)
	{
		fork[i].id = i + 1;
		pthread_mutex_init(&fork[i].mutex, NULL);
		i++;
	}
	data->fork = fork;
}

void init_philos(t_data *data)
{
	int i;
	t_philo *philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->number_philos);
	i = 0;
	while (i < data->number_philos)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &data->fork[i];
		philo[i].right_fork = &data->fork[(i + 1) % data->number_philos];
		philo[i].last_meal = data->start_time;
		philo[i].data = data;
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		i++;
	}
	data->philo = philo;
}

void print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->someone_died_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		return ;
	}
	printf("%lld %d %s\n", get_current_time(), philo->id, str);
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
}

void eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_usleep(1);
	pthread_mutex_lock(&philo->left_fork->mutex);
	print(philo, "has taken a fork");
	// printf("%lld %d has taken a fork \n", get_current_time(), philo->id);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	// printf("%lld %d has taken a fork \n", get_current_time(), philo->id);
	// printf("%lld %d is eating \n", get_current_time(), philo->id);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void sleep_philo(t_philo *philo)
{
	print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void think(t_philo *philo)
{
	print(philo, "is thinking");
}

void *routine_philosopher(void *dt)
{
	t_philo *philo;

	philo = (t_philo *)dt;
	while (1)
	{
		pthread_mutex_lock(&philo->data->someone_died_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->someone_died_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		eat(philo);
		sleep_philo(philo);
		think(philo);
		ft_usleep(1);
	}
	return NULL;
}

void *is_dead_th(void *dt)
{
	int i;
	t_data *data;

	data = (t_data *)dt;
	while (1)
	{
		i = 0;
		while (i < data->number_philos)
		{
			pthread_mutex_lock(&data->philo[i].last_meal_mutex);
			if ((get_current_time() - data->philo[i].last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
				pthread_mutex_lock(&data->someone_died_mutex);
				printf("%lld %d died\n", get_current_time(), data->philo[i].id);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->someone_died_mutex);
				pthread_mutex_unlock(&data->print_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			i++;
		}
		ft_usleep(600);
	}
	return NULL;
}
void start_simulation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, routine_philosopher, &data->philo[i]);
		i++;
	}
	pthread_create(&data->thread_monitoring, NULL, is_dead_th, data);
}

void waintg_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->thread_monitoring, NULL);
}
/* number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
 */
void init_data(t_data *data, int ac, char **av)
{
	data->number_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->someone_died = 0;
	if (ac == 6)
		data->number_must_eat = ft_atoi(av[5]);
	else
		data->number_must_eat = -1;
	data->start_time = get_current_time();
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->someone_died_mutex, NULL);
}

int main(int ac, char **av)
{
	// t_philo *philo = NULL;
	t_data data;

	ft_check_args_quant(ac);
	check_valid_numbers(av);
	check_philo_number(av);
	init_data(&data, ac, av);
	init_forks(&data);
	init_philos(&data);
	start_simulation(&data);
	waintg_threads(&data);
	// routine
	// monitoring
	exit(0);
}