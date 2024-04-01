#include <philo.h>

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	printf("%i has taken left fork\n", philo->id);
	pthread_mutex_lock(&philo->right_fork->fork);
	printf("%i has taken right fork\n", philo->id);
	philo->eating = 1;
	printf("%i is eating\n", philo->id);
	pthread_mutex_lock(philo->meal_lock);
	usleep(philo->table->time_to_eat);
	philo->meals_counter++;
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void nap(t_philo *philo)
{
	printf("%i is sleeping\n", philo->id);
	usleep(philo->table->time_to_sleep);
}

void think(t_philo *philo)
{
	printf("%i is thinking\n", philo->id);
}

int dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void *philo_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id %2 == 0)
	{
		usleep(1);
	}
	while (!dead_loop(philo))
	{
		eat(philo);
		nap(philo);
	}
	return (pointer);
}

int thread_create(t_table *table)
{
	// pthread_t observer;
	int i;

	// TODO: Create the monitor process


	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, 
		&philo_routine, &table->philos[i]) != 0)
		{
			ft_error("maybe leaks here!");
		}
	}
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			ft_error("maybe leaks here!");
		}
		i++;
	}
	return 0;
}


/*
This is the main function:
./philo 5 800 200 200 [5]
*/
int	main(int ac, char **av)
{
	t_table table;
	(void)ac;

	if (ac < 5 || ac > 6)
	{
		ft_error("Error: Invalid number of arguments");
		return (1);
	}
	if (parse_input(&table, av))
	{
		ft_error("Error in parse inputs!");
		return 1;
	}
	if (init_table(&table))
	{
		ft_error("Error in init_table!");
		return 1;
	}
	if (init_philo(&table))
	{
		ft_error("Error in init_philo!");
		return 1;
	}

	assign_fork(&table);
	printf("\t\t\ttable->n_philos = %i\n \
			table->time_to_die = %i\n \
			table->time_to_eat = %i\n \
			table->time_to_sleep = %i\n \
			table->n_limit_meals = %i\n", 
			table.n_philos,
			table.time_to_die,
			table.time_to_eat,
			table.time_to_sleep,
			table.n_limit_meals);
	int i = -1;
	while (++i < table.n_philos)
	{
		printf("table->philos[%i].id = %i\n", i, table.philos[i].id);
		printf("\ttable->philos[%i].left_fork = %i\n", i, table.philos[i].left_fork->fork_id);
		printf("\ttable->philos[%i].right_fork = %i\n", i, table.philos[i].right_fork->fork_id);
	}
	thread_create(&table);
	return (0);
}




