/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:44:29 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/05/15 08:44:30 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	safe_lock_handle(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, PTHREAD_MUTEX_NORMAL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		ft_error("Wrong code for lock!");
}

void	destroy_all(bool error, t_table *table)
{
	int	i;

	i = 0;
	safe_lock_handle(&table->table_lock, DESTROY);
	safe_lock_handle(&table->write_lock, DESTROY);
	while (i < table->n_philos)
	{
		safe_lock_handle(&table->forks[i].fork, DESTROY);
		safe_lock_handle(&table->philos[i].philo_lock, DESTROY);
		i++;
	}
	if (error)
	{
		ft_error("Error!");
	}
}
