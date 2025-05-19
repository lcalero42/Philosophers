/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:35:26 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 20:34:31 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static long long	get_timestamp_ms(void);

void	*philosopher_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	if (philo->id % 2 == 0)
		usleep(1000); // Small desync to avoid deadlocks at startup

	while (1)
	{
		// Check if simulation should stop
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);

		// Take forks
		pthread_mutex_lock(&data->forks[philo->left_fork_id].mutex);
		printf("time %lld - philosopher %d has taken left fork\n", 
			get_timestamp_ms() - data->start_time, philo->id);

		pthread_mutex_lock(&data->forks[philo->right_fork_id].mutex);
		printf("time %lld - philosopher %d has taken right fork\n", 
			get_timestamp_ms() - data->start_time, philo->id);

		// Eat
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = get_timestamp_ms();
		pthread_mutex_unlock(&philo->last_meal_mutex);

		printf("time %lld - philosopher %d is eating\n", 
			get_timestamp_ms() - data->start_time, philo->id);

		usleep(data->time_eat * 1000);

		philo->meals_eaten++;

		// Put down forks
		pthread_mutex_unlock(&data->forks[philo->right_fork_id].mutex);
		pthread_mutex_unlock(&data->forks[philo->left_fork_id].mutex);

		// Sleep
		printf("time %lld - philosopher %d is sleeping\n", 
			get_timestamp_ms() - data->start_time, philo->id);
		usleep(data->time_sleep * 1000);

		// Think
		printf("time %lld - philosopher %d is thinking\n", 
			get_timestamp_ms() - data->start_time, philo->id);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			long long	now = get_timestamp_ms();
			pthread_mutex_lock(&data->philosophers[i].last_meal_mutex);
			if (now - data->philosophers[i].last_meal >= data->time_death)
			{
				pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
				pthread_mutex_lock(&data->stop_mutex);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->stop_mutex);

				printf("Philosopher %d has died\n", data->philosophers[i].id);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
			i++;
		}
	}
}

static long long	get_timestamp_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}
