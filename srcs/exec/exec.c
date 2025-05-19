/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 20:29:06 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	join_threads(t_data *data);
static void	create_threads(t_data *data);
static void cleanup(t_data *data);

void	exec(t_data *data)
{
	pthread_t	monitor_thread;

	pthread_mutex_init(&data->stop_mutex, NULL);
	data->stop_simulation = 0;
	create_threads(data);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		perror("Failed to create monitor thread");
		exit(EXIT_FAILURE);
	}
	pthread_join(monitor_thread, NULL);
	join_threads(data);
	cleanup(data);
}

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philosophers[i].thread_id, NULL, philosopher_routine, &data->philosophers[i]);
		i++;
	}
}

static void	join_threads(t_data *data)
{
	int	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
}

static void cleanup(t_data *data)
{
    int i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_destroy(&data->philosophers[i].last_meal_mutex);
        pthread_mutex_destroy(&data->forks[i].mutex);
        i++;
    }
    pthread_mutex_destroy(&data->stop_mutex);
}
