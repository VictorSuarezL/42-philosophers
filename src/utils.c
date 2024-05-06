/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:01:27 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/08 16:42:06 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
	{
		return (1);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void print_action(t_philo *philo, char *str)
{
	size_t time;

	safe_lock_handle(&philo->table->write_lock, LOCK);
	time = get_current_time() - philo->table->start_simulation;
	printf("[%ld] %i %s\n", time, philo->id, str);
	safe_lock_handle(&philo->table->write_lock, UNLOCK);
}

void increase(t_mtx *mtx, int *value)
{
	safe_lock_handle(mtx, LOCK);
	(*value)++;
	safe_lock_handle(mtx, UNLOCK);
}
