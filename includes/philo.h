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
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// STRUCTURES:
typedef enum e_code		t_code;
typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

// ERROR:
void					ft_putendl_fd(char *s, int fd);
void					ft_error(char *msg);

// SAFE FUNCTIONS:
void					safe_lock_handle(t_mtx *mutex, t_code code);
void					destroy_all(bool end, t_table *table);

// MONITOR:
void					*monitor(void *pointer);
bool					simulation_finished(t_table *table);
// void monitor(t_table	*table);

// ROUTINES:
void					taking_forks(t_philo *philo);
void					eat(t_philo *philo);
void					nap(t_philo *philo);
void					think(t_philo *philo);
void					wait_all_thd_ready(t_table *table);

// SET AND GET:
void					set_bool(t_mtx *mtx, bool *dest, bool value);
bool					get_bool(t_mtx *mtx, bool *value);
void					set_long(t_mtx *mutex, size_t *dest, size_t value);
size_t					get_long(t_mtx *mutex, size_t *value);

// UTILS:
int						ft_isdigit(int i);
int						ft_usleep(size_t milliseconds);
size_t					get_current_time(void);
void					print_action(t_philo *philo, char *str);
void					increase(t_mtx *mtx, int *value);

// PARSE_INPUT:
int						check_args(int ac, char **av);
int						parse_input(t_table *table, char **av);

// INIT:
int						init_table(t_table *table);
int						init_philo(t_table *table);
void					assign_fork(t_table *table);

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_code;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			thread_id;
	int					id;
	int					eating;
	int					*dead;
	t_table				*table;
	int					meals_counter;
	bool				full;
	size_t				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_mtx				philo_lock;
}						t_philo;

typedef struct s_table
{
	int					aux_counter;
	int					n_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					n_limit_meals;
	pthread_t			observer;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_lock;
	t_mtx				write_lock;
	long				start_simulation;
	bool				all_threads_ready;
	bool				end_simulation;
	int					n_thd_running;
}						t_table;

#endif
