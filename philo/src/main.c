#include "philosopher.h"

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
		philo[i].count_mealded = 0;
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
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
		return;
	}

	printf("%lld %d %s\n", get_current_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
}
int check_someone_died(t_data *data)
{
    int died;
    
    pthread_mutex_lock(&data->someone_died_mutex);
    died = data->someone_died;
    pthread_mutex_unlock(&data->someone_died_mutex);
    
    return died;
}
void eat(t_philo *philo)
{
	if (check_someone_died(philo->data) == 1)
		return;
	pthread_mutex_lock(&philo->left_fork->mutex);
	print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->count_mealded++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	ft_usleep(philo->data->time_to_eat);
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
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&philo->data->someone_died_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->someone_died_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		
		eat(philo);
		sleep_philo(philo);
		think(philo);
		//ft_usleep(1);
	}

	return NULL;
}

int check_all_ate(t_data *data)
{
	int i = 0;
	int all_ate_enough = 1;

	if (data->number_must_eat <= 0)
		return (0);
	while (i < data->number_philos)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (data->philo[i].count_mealded < data->number_must_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	if (all_ate_enough)
	{
		data->someone_died = 1;
		pthread_mutex_unlock(&data->someone_died_mutex);
		return (1);
	}
	return (0); // Ainda não
}

int check_death(t_data *data)
{
	int i = 0;

	while (i < data->number_philos)
	{
		pthread_mutex_lock(&data->philo[i].last_meal_mutex);
		if ((get_current_time() - data->philo[i].last_meal) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
		//	pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			printf("%lld %d died\n", get_current_time() - data->start_time, data->philo[i].id);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
			pthread_mutex_unlock(&data->someone_died_mutex);
			pthread_mutex_unlock(&data->print_mutex);
			return (1); // Alguém morreu
		}
		pthread_mutex_unlock(&data->philo[i].last_meal_mutex);
		i++;
	}
	return (0); // Ninguém morreu
}

void *is_dead_th(void *dt)
{
	t_data *data;

	data = (t_data *)dt;
	while (1)
	{
		pthread_mutex_lock(&data->someone_died_mutex);
		if(check_death(data) == 1)
			return (NULL);
		if (data->number_must_eat > 0)
			if(check_all_ate(data) == 1)
				return (NULL);
		pthread_mutex_unlock(&data->someone_died_mutex);
	}
	return NULL;
}
int start_simulation(t_data *data)
{
	int i;

	i = 0;
	if (data->number_philos == 1)
	{
		print(&data->philo[0], "has taken a fork");
		ft_usleep(data->time_to_die);
		printf("%lld %d died\n", get_current_time(), data->philo[0].id);
		data->someone_died = 1;
		return (0);
	}

	while (i < data->number_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, routine_philosopher, &data->philo[i]);
		i++;
	}
	pthread_create(&data->thread_monitoring, NULL, is_dead_th, data);
	return (1);
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
	t_data data;

	ft_check_args_quant(ac);
	check_valid_numbers(av);
	check_philo_number(av);
	init_data(&data, ac, av);
	init_forks(&data);
	init_philos(&data);
	if (start_simulation(&data))
	{
		waintg_threads(&data);
	}
	exit(0);
}