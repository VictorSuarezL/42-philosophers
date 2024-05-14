/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:15:57 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/08 13:21:07 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * Initializes the table with philosophers and forks.
 *
 * @param table The table structure to initialize.
 * @return 0 if initialization is successful, 1 otherwise.
 */
int	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->philos = (t_philo *)malloc(table->n_philos * sizeof(t_philo));
	if (!table->philos)
	{
		return (1);
	}
	table->forks = (t_fork *)malloc(table->n_philos * sizeof(t_fork));
	if (!table->forks)
	{
		return (1);
	}
	safe_lock_handle(&table->table_lock, INIT);
	safe_lock_handle(&table->write_lock, INIT);
	// pthread_mutex_init(&table->table_lock, PTHREAD_MUTEX_NORMAL);
	// pthread_mutex_init(&table->write_lock, PTHREAD_MUTEX_NORMAL);
	while (++i < table->n_philos)
	{
		safe_lock_handle(&table->forks[i].fork, INIT);

		// pthread_mutex_init(&table->forks[i].fork, PTHREAD_MUTEX_NORMAL);
		table->forks[i].fork_id = i;
	}
	return (0);
}

/**
 * Initializes the philosophers in the table.
 *
 * @param table The table structure containing the philosophers.
 * @return 0 if successful, -1 otherwise.
 */
int	init_philo(t_table *table)
{
	int	i;
	
	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].last_meal_time = 0;
		// table->philos[i].dead = &table->dead_flag;
		// table->philos[i].dead_lock = &table->dead_lock;
		// table->philos[i].meal_lock = &table->meal_lock;
		// table->philos[i].write_lock = &table->write_lock;
		safe_lock_handle(&table->philos[i].philo_lock, INIT);
		
		// pthread_mutex_init(&table->philos[i].philo_lock, PTHREAD_MUTEX_NORMAL);
		table->philos[i].table = table;
	}
	return (0);
}

/**
 * Assigns forks to each philosopher in the table.
 *
 * @param table The table struct containing the philosophers and forks.
 */
void	assign_fork(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].left_fork = &table->forks[i];
		if (i == 0)
			table->philos[i].right_fork = &table->forks[table->n_philos - 1];
		else
			table->philos[i].right_fork = &table->forks[i - 1];
	}
}
