/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:16:05 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/01 13:52:28 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_philo *philo)
{
	if (philo->id%2 == 0)
	{
		safe_lock_handle(&philo->left_fork->fork, LOCK);
		print_action(philo, "has taken a fork left");

		// printf("%i has taken left fork id = %i\n", philo->id-1, philo->left_fork->fork_id);
		safe_lock_handle(&philo->right_fork->fork, LOCK);
		print_action(philo, "has taken a fork right");
		// printf("%i has taken right fork id = %i\n", philo->id-1, philo->right_fork->fork_id);
	}
	else
	{
		safe_lock_handle(&philo->right_fork->fork, LOCK);
		print_action(philo, "has taken a fork right");
		// printf("%i has taken right fork id = %i\n", philo->id-1, philo->right_fork->fork_id);
		safe_lock_handle(&philo->left_fork->fork, LOCK);
		print_action(philo, "has taken a fork left");
		// printf("%i has taken left fork id = %i\n", philo->id-1, philo->left_fork->fork_id);
	}
	
	
	safe_lock_handle(&philo->philo_lock, LOCK);
	// philo->table->aux_counter++;
	// printf("%i is eating\n", philo->id-1);
	print_action(philo, "is eating");
	// printf("-->aux_counter = %i\n", philo->table->aux_counter);
	// philo->eating = 1;
	ft_usleep(philo->table->time_to_eat);
	// usleep(philo->table->time_to_eat);
	philo->meals_counter++;
	safe_lock_handle(&philo->philo_lock, UNLOCK);
	// philo->eating = 0;
	safe_lock_handle(&philo->left_fork->fork, UNLOCK);
	safe_lock_handle(&philo->right_fork->fork, UNLOCK);
}

void	nap(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void think(t_philo *philo)
{
	print_action(philo, "is_thinking");
}

// void	think(t_philo *philo)
// {
// 	printf("%i is thinking\n", philo->id);
// }

// int	dead_loop(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (*philo->dead == 1)
// 		return (pthread_mutex_unlock(philo->dead_lock), 1);
// 	pthread_mutex_unlock(philo->dead_lock);
// 	return (0);
// }

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	// if (philo->id % 2 == 0)
	// {
	// 	// ft_putendl_fd("sleeping!", 1);
	// 	// printf("sleeping!\n");
	// 	usleep(100);
	// }
	// while (!dead_loop(philo))
	while (1)
	{
		// print_action(philo, "is eating");

		eat(philo);
		nap(philo);
		think(philo);
		// ft_usleep(2000);
	}
	return (pointer);
}

int	thread_create(t_table *table)
{
	int	i;
	pthread_t observer;


	if(pthread_create(&observer, NULL, &monitor, &table) != 0)
	{
		ft_error("maybe leaks here! destoy");
	}
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
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
	return (0);
}

/*
This is the main function:
./philo 5 800 200 200 [5]
*/
int	main(int ac, char **av)
{
	t_table	table;
	// int		i;

	// (void)ac;
	if (ac < 5 || ac > 6)
		ft_error("Error: Invalid number of arguments");
	if (check_args(ac, av))
		ft_error("Invalid args");
	if (parse_input(&table, av))
	{
		ft_error("Error in parse inputs!");
		return (1);
	}
	if (init_table(&table))
	{
		ft_error("Error in init_table!");
		return (1);
	}
	if (init_philo(&table))
	{
		ft_error("Error in init_philo!");
		return (1);
	}
	assign_fork(&table);
	// printf("\t\t\ttable->n_philos = %i\n \
	// 		table->time_to_die = %i\n \
	// 		table->time_to_eat = %i\n \
	// 		table->time_to_sleep = %i\n \
	// 		table->n_limit_meals = %i\n",
	// 		table.n_philos,
	// 		table.time_to_die,
	// 		table.time_to_eat,
	// 		table.time_to_sleep,
	// 		table.n_limit_meals);
	// int i;
	// i = -1;
	// while (++i < table.n_philos)
	// {
	// 	printf("table->philos[%i].id = %i\n", i, table.philos[i].id);
	// 	printf("\ttable->philos[%i].left_fork = %i\n", i,
	// 		table.philos[i].left_fork->fork_id);
	// 	printf("\ttable->philos[%i].right_fork = %i\n", i,
	// 		table.philos[i].right_fork->fork_id);
	// }
	thread_create(&table);
	return (0);
}
