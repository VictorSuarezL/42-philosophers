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

void	wait_all_thd_ready(t_table *table)
{
	int	i;

	i = 0;
	while (!table->all_threads_ready)
	{
		(void)i;
	}
}