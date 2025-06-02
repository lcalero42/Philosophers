/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:18:24 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/02 13:38:44 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_threads(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->threads_ready == data->nb_philo)
		{
			data->start_time = get_timestamp_ms();
			data->all_threads_ready = 1;
			pthread_mutex_unlock(&data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->start_mutex);
		usleep(100);
	}
}

void	sync_philo_routine(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->start_mutex);
	data->threads_ready++;
	pthread_mutex_unlock(&data->start_mutex);
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->all_threads_ready)
		{
			pthread_mutex_unlock(&data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->start_mutex);
		usleep(100);
	}
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}

void	sync_monitor_routine(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->all_threads_ready)
		{
			pthread_mutex_unlock(&data->start_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->start_mutex);
		usleep(100);
	}
}
