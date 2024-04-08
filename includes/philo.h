/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 09:15:39 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/04/08 16:06:02 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
typedef enum e_code t_code;
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_philo t_philo;


// ERROR:
void	ft_putendl_fd(char *s, int fd);
void	ft_error(char *msg);

// SAFE FUNCTIONS:
void safe_lock_handle(t_mtx *mutex, t_code code);

// MONITOR:
void *monitor(void *pointer);
// void monitor(t_table	*table);


// SET AND GET:
void set_bool(t_mtx *mtx, bool *dest, bool value);
bool get_bool(t_mtx *mtx, bool *value);

// UTILS:
int	ft_isdigit(int i);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
void print_action(t_philo *philo, char *str);
void increase(t_mtx *mtx, int *value);


// PARSE_INPUT:
int check_args(int ac, char **av);
int	parse_input(t_table *table, char **av);

// INIT:
int	init_table(t_table *table);
int init_philo(t_table *table);
void assign_fork(t_table *table);

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_code;

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
	t_table				*table;
	int				meals_counter;
	bool				full;
	// long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mtx				philo_lock;
	// t_mtx				*dead_lock;
	// t_mtx				*meal_lock;
	// t_mtx				*write_lock;
}						t_philo;

typedef struct s_table
{
	// AUX VARIABLES:
	int 			aux_counter;
	// ARG VARIABLES:
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_limit_meals;
	pthread_t		observer;
	// RUN VARIABLES:
	// int					dead_flag;
	t_fork				*forks;
	t_philo				*philos;
	// t_mtx				dead_lock;
	t_mtx				table_lock;
	t_mtx				write_lock;
	long				start_simulation;
	bool 				all_threads_ready;
	bool				end_simulation;
	int					n_thd_running;
}						t_table;

#endif
