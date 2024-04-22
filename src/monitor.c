/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:47:50 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/22 16:01:23 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_all_ate(t_table *table)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (table->n_limit_meals == -1)
	{
		return (0);
	}
	while (i < table->n_philos)
	{
		safe_lock_handle(&table->philos[i].philo_lock, LOCK);
		if (table->philos[i].meals_counter >= table->n_limit_meals)
		{
			done_eating++;
		}
		safe_lock_handle(&table->philos[i].philo_lock, UNLOCK);
		i++;
	}
	if (done_eating == table->n_philos)
	{
		return (1);
	}
	return (0);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	res;

	safe_lock_handle(mtx, LOCK);
	res = *value;
	safe_lock_handle(mtx, UNLOCK);
	return (res);
}

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_lock_handle(mtx, LOCK);
	*dest = value;
	safe_lock_handle(mtx, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_lock, &table->end_simulation));
}

bool all_philo_thd_running(t_mtx *mtx, int *n_thd, int n_philos)
{
	bool res;

	res = false;
	safe_lock_handle(mtx, LOCK);

	if (*n_thd == n_philos)
	{
		res = true;
	}
	safe_lock_handle(mtx, UNLOCK);
	return(res);
}

// void monitor(t_table	*table)
void	*monitor(void *pointer)
{
	t_table	*table;
	int		i;

	table = (t_table *)pointer;

	// safe_lock_handle(&table->table_lock, LOCK);
	// printf("n_philo_in_monitor = %i\n", table->n_philos);
	// printf("n_thd_running_in_monitor = %i\n", table->n_thd_running);
	// safe_lock_handle(&table->table_lock, UNLOCK);

	i = -1;
	while (!all_philo_thd_running(&table->table_lock, &table->n_thd_running, table->n_philos))
	{
		// i++;
		printf("->waiting!\n");
		ft_usleep(2000);
	}
	if (all_philo_thd_running(&table->table_lock, &table->n_thd_running, table->n_philos))
	{
		printf("all threads ready!\n");
	}

	while (!simulation_finished(table))
	{
		i = -1;
		while (++i<table->n_philos && !simulation_finished(table))
		{
		    print_action(&table->philos[i], "simul not finished");
		    // ft_usleep(2000);
		    if (check_all_ate(table) == 1)
		    {
		        set_bool(&table->table_lock, &table->end_simulation, true);
		        print_action(&table->philos[i], "ALL ATE!");
				break;
		    }
		}
		// while (++i < table->n_philos)
		// {
		// 	// printf("hello!\n");
		// 	print_action(&table->philos[i], "simul not finished");
		// 	ft_usleep(2000);
		// }
		// printf("simulation not finished!\n");
		// ft_usleep(2000);
	}
	return (NULL);
}
