/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:16:11 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/05/15 11:08:17 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	nb;
	int	sign;
	int	i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	parse_input(t_table *table, char **av)
{
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->n_thd_running = 0;
	table->aux_counter = 0;
	table->n_philos = ft_atoi(av[1]);
	if (table->n_philos > 200)
		return (1);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		table->n_limit_meals = ft_atoi(av[5]);
		if (table->n_limit_meals == 0)
		{
			return (1);
		}
	}
	else
		table->n_limit_meals = -1;
	return (0);
}
