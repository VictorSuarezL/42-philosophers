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

	i = -1;
	if (pthread_create(&table->observer, NULL, &monitor, table) != 0)
		destroy_all(true, table);
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
			destroy_all(true, table);
		increase(&table->table_lock, &table->n_thd_running);
	}
	table->start_simulation = get_current_time();
	set_bool(&table->table_lock, &table->all_threads_ready, true);
	i = -1;
	if (pthread_join(table->observer, NULL) != 0)
		destroy_all(true, table);
	while (++i < table->n_philos)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			destroy_all(true, table);
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
