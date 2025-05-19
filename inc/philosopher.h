/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:36:41 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 15:25:01 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define MAX_PHILO 250

typedef enum e_state
{
		SLEEPING,
		THINKING,
		EATING,
}		t_state;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	t_state			state;
} t_philo;

typedef struct s_data
{
	t_philo		philosophers[MAX_PHILO];
	int			nb_philo;
	int			time_death;
	int			time_eat;
	int			time_sleep;
	int			nb_eat;
	long long	start_time;
} t_data;

void	parse_input(char **av, t_data *data, struct timeval *tv);
int		ft_atoi(const char *nptr);

#endif