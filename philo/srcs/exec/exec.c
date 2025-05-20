/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 13:53:21 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	create_threads(t_data *data);

void	exec(t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_mutex_init(&data->stop_mutex, NULL))
		ret_error(data, "Failed to init mutex\n");
	if (pthread_mutex_init(&data->print_mutex, NULL))
		ret_error(data, "Failed to init mutex\n");
	data->stop_simulation = 0;
	data->start_time = get_timestamp_ms();
	create_threads(data);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
		ret_error(data, "Failed to create monitor thread\n");
	pthread_join(monitor_thread, NULL);
	set_simulation_stop(data);
	join_threads(data);
	cleanup(data);
}

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philosophers[i].thread_id, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
		{
			perror("Failed to create philosopher thread\n");
			set_simulation_stop(data);
			while (--i >= 0)
				pthread_join(data->philosophers[i].thread_id, NULL);
			cleanup(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philosophers[i].last_meal_mutex);
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}
