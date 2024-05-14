/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:16:05 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/22 13:48:21 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		safe_lock_handle(&philo->left_fork->fork, LOCK);
		print_action(philo, "has taken a fork left");
		safe_lock_handle(&philo->right_fork->fork, LOCK);
		print_action(philo, "has taken a fork right");
	}
	else
	{
		safe_lock_handle(&philo->right_fork->fork, LOCK);
		print_action(philo, "has taken a fork right");
		if (philo->table->n_philos == 1)
		{
			ft_usleep(philo->table->time_to_die);
			safe_lock_handle(&philo->right_fork->fork, UNLOCK);
			return ;
		}
		safe_lock_handle(&philo->left_fork->fork, LOCK);
		print_action(philo, "has taken a fork left");
	}
}

void	eat(t_philo *philo)
{
	if (!simulation_finished(philo->table))
	{
		taking_forks(philo);
		set_long(&philo->philo_lock, &philo->last_meal_time,
			get_current_time());
		philo->meals_counter++;
		print_action(philo, "is eating");
		ft_usleep(philo->table->time_to_eat);
		if (philo->table->n_limit_meals > 0
			&& philo->meals_counter == philo->table->n_limit_meals)
			set_bool(&philo->philo_lock, &philo->full, true);
		// if (philo->table->n_philos != 1)
		safe_lock_handle(&philo->left_fork->fork, UNLOCK);
		safe_lock_handle(&philo->right_fork->fork, UNLOCK);
	}
}

void	nap(t_philo *philo)
{
	print_action(philo, "is sleeping");
	if (philo->table->n_philos != 1)
		ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo->table->n_philos != 1)
		print_action(philo, "is thinking");
}

// int	dead_loop(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->dead_lock);
// 	if (*philo->dead == 1)
// 		return (pthread_mutex_unlock(philo->dead_lock), 1);
// 	pthread_mutex_unlock(philo->dead_lock);
// 	return (0);
// }

void	wait_all_thd_ready(t_table *table)
{
	while (!table->all_threads_ready)
	{
		;
	}
}

// void	de_synchronize_philos(t_philo *philo)
// {
// 	if (philo->table->n_philos % 2 == 0)
// 	{
// 		if (philo->id % 2 == 0)
// 			ft_usleep(30);
// 	}
// 	else
// 	{
// 		if (philo->id % 2)
// 			think(philo);
// 		ft_usleep(30);
// 	}
// }

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	wait_all_thd_ready(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_lock, &philo->full))
		{
			break ;
		}
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (pointer);
}

void	thread_create(t_table *table)
{
	int			i;
	pthread_t	observer;

	i = -1;
	if (table->n_limit_meals == 0)
		return ;
	if (pthread_create(&table->observer, NULL, &monitor, table) != 0)
	{
		destroy_all(true, table);
	}
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
		{
			destroy_all(true, table);
		}
		increase(&table->table_lock, &table->n_thd_running);
	}
	table->start_simulation = get_current_time();
	set_bool(&table->table_lock, &table->all_threads_ready, true);
	i = -1;
	if (pthread_join(table->observer, NULL) != 0)
	{
		destroy_all(true, table);
	}
	while (++i < table->n_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
		{
			destroy_all(true, table);
		}
		i++;
	}
	set_bool(&table->table_lock, &table->end_simulation, true);
}

/*
This is the main function:
./philo 5 800 200 200 [5]
*/
int	main(int ac, char **av)
{
	t_table	table;

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
	thread_create(&table);
	destroy_all(false, &table);
	return (0);
}
