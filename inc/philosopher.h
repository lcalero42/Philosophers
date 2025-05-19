/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:36:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 20:01:36 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

# define MAX_PHILO 250

typedef enum e_state
{
		SLEEPING,
		THINKING,
		EATING,
}		t_state;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
} 		t_fork;

typedef struct s_philo
{
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread_id;
	t_state			state;
	pthread_mutex_t	last_meal_mutex;

	struct s_data 	*data;
}	t_philo;

typedef struct s_data
{
	t_philo		philosophers[MAX_PHILO];
	t_fork		forks[MAX_PHILO];
	int			nb_philo;
	int			time_death;
	int			time_eat;
	int			time_sleep;
	int			nb_eat;
	long long	start_time;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
} 		t_data;


//FUNCTIONS
void	parse_input(char **av, t_data *data, struct timeval *tv);
int		ft_atoi(const char *nptr);
void	exec(t_data *data);
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

#endif