#ifndef PHILO_H
# define PHILO_H

// LIBRARIES:
# include <limits.h> // INT_MAX
// mutex: init destroy lock unlock; threads: create join detach
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // get time of day
# include <unistd.h>   // write, sleep

// STRUCTURES:
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

// UTILS:
void	ft_error(char *msg);

// PARSE_INPUT:
int	parse_input(t_table *table, char **av);

// INIT:
int	init_table(t_table *table);
int init_philo(t_table *table);
void assign_fork(t_table *table);


typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t 			thread_id; // a philo is a thread
	int					id;
	int 				eating;
	int 				*dead;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_table				*table;
	int				meals_counter;
	bool				full;
	// long				last_meal_time;
	// t_mtx				philo_lock;
	t_mtx				*dead_lock;
	t_mtx				*meal_lock;
	t_mtx				*write_lock;
}						t_philo;

// typedef struct s_philo
// {
// 	pthread_t		thread;
// 	int				id;
// 	int				meals_eaten;
// 	size_t			time;
// 	size_t			die_ms;
// 	size_t			eat_ms;
// 	size_t			sleep_ms;
// 	size_t			start_ms;
// 	size_t			meal_duration;
// 	int				n_of_philos;
// 	int				n_of_meals;
// 	bool			*dead;
// 	pthread_mutex_t	*write_lock;
// 	pthread_mutex_t	*dead_lock;
// 	pthread_mutex_t	*meal_lock;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t	*l_fork;

// }					t_philo;

typedef struct s_table
{
	// ARG VARIABLES:
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_limit_meals;
	// RUN VARIABLES:
	int					dead_flag;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				dead_lock;
	t_mtx				meal_lock;
	t_mtx				write_lock;
	// long				start_simulation;
	// long				end_simulation;
}						t_table;

#endif