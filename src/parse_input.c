/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:16:11 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/01 10:50:09 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// static long	ft_atol(const char *str)
// {
// 	int		i;
// 	int		is_negative;
// 	long	res;

// 	i = 0;
// 	res = 0;
// 	is_negative = 1;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		// ft_error("Error");
// 		return -1;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		res = res * 10 + str[i] - '0';
// 		++i;
// 	}
// 	if ((res <= INT_MAX && res >= 0) && (str[0] >= '0' && str[0] <= '9'))
// 		return (is_negative * res);
// 	else
// 	{
// 		// ft_error("Error");
// 		return -1;
// 	}
// }

int check_args(int ac, char **av)
{
	int i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return 1;
		}
		i++;
	}
	return 0;
}

int	ft_atoi(char *str)
{
	int 	nb;
	int					sign;
	int					i;

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
	// table->dead_flag = 0;
	table->start_simulation = get_current_time();
	table->aux_counter = 0;
	table->n_philos = ft_atoi(av[1]);
    if (table->n_philos > 200)
        return(1);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	// if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
	// 	|| table->time_to_sleep < 6e4)
	// 	return(1);
	if (av[5])
		table->n_limit_meals = ft_atoi(av[5]);
	else
		table->n_limit_meals = -1;
    return (0);
}

// int init_philo(t_table *table, char)
