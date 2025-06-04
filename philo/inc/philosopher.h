/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:36:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/04 14:10:58 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

//MACROS
# define MAX_PHILO 250

//STRCUTS
typedef struct s_fork
{
	int				is_taken;
	pthread_mutex_t	mutex;
}		t_fork;

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread_id;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_mutex;

	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			philosophers[MAX_PHILO];
	t_fork			forks[MAX_PHILO];
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	long long		start_time;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	fork_access_mutex;
	int				threads_ready;
	int				all_threads_ready;
}		t_data;

//FUNCTIONS
void		parse_input(char **av, t_data *data, struct timeval *tv, int ac);
int			ft_atoi(const char *nptr);
void		exec(t_data *data);
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
int			philo_cycle(t_philo *philo, int *has_forks);

//PHILO ACTIONS
int			take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);

//PHILO UTILS
long long	get_timestamp_ms(void);
void		print_status(t_data *data, int id, char *status, int should_print);
int			check_simulation_stop(t_data *data);
void		set_simulation_stop(t_data *data);
void		update_last_meal(t_philo *philo);
void		join_threads(t_data *data);
void		cleanup(t_data *data);
void		ft_usleep(int time, t_data *data);
void		wait_threads(t_data *data);
void		sync_philo_routine(t_data *data, t_philo *philo);
void		sync_monitor_routine(t_data *data);
void		get_fork_order(t_philo *philo, int *first, int *second);
void		release_forks(t_data *data, int first_fork, int second_fork);
int			acquire_fork(t_data *data, int fork_id, int philo_id);
void		check_meals(int local_meals, t_data *data);
int			check_limit_reached(t_philo *philo);

//ERROR HANDLING
void		ret_error(t_data *data, const char *error_mess);
int			check_params(t_data *data, int ac);

#endif