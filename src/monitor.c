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

static bool	philo_died(t_philo *philo)
{
	size_t	elapsed;

	if (get_bool(&philo->philo_lock, &philo->full))
		return (false);
	elapsed = get_current_time() - get_long(&philo->philo_lock,
			&philo->last_meal_time);
	if (elapsed > philo->table->time_to_die && philo->last_meal_time > 0)
	{
		return (true);
	}
	if (philo->table->n_philos == 1)
	{
		ft_usleep(1);
		return (true);
	}
	return (false);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_lock, &table->end_simulation));
}

bool	all_philo_thd_running(t_mtx *mtx, int *n_thd, int n_philos)
{
	bool	res;

	res = false;
	safe_lock_handle(mtx, LOCK);
	if (*n_thd == n_philos)
	{
		res = true;
	}
	safe_lock_handle(mtx, UNLOCK);
	return (res);
}

void	*monitor(void *pointer)
{
	t_table	*table;
	int		i;

	table = (t_table *)pointer;
	i = -1;
	while (!all_philo_thd_running(&table->table_lock, &table->n_thd_running,
			table->n_philos))
		i = 1;
	i = -1;
	while (++i < table->n_philos && !simulation_finished(table))
	{
		if (philo_died(table->philos + i))
		{
			print_action(table->philos + i, "DEAD");
			set_bool(&table->table_lock, &table->end_simulation, true);
		}
		if (check_all_ate(table) == 1)
		{
			set_bool(&table->table_lock, &table->end_simulation, true);
			break ;
		}
	}
	return (NULL);
}
