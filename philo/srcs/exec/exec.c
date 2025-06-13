/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/13 14:16:58 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	create_threads(t_data *data);
static void	handle_single_philosopher(t_data *data);

void	exec(t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_mutex_init(&data->stop_mutex, NULL))
		ret_error(data, "Failed to init mutex\n");
	if (pthread_mutex_init(&data->print_mutex, NULL))
		ret_error(data, "Failed to init mutex\n");
	if (pthread_mutex_init(&data->start_mutex, NULL))
		ret_error(data, "Failed to init start mutex\n");
	if (pthread_mutex_init(&data->fork_access_mutex, NULL))
		ret_error(data, "Failed to init fork mutex\n");
	if (data->nb_philo == 1)
	{
		handle_single_philosopher(data);
		cleanup(data);
		return ;
	}
	create_threads(data);
	wait_threads(data);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
		ret_error(data, "Failed to create monitor thread\n");
	pthread_join(monitor_thread, NULL);
	set_simulation_stop(data);
	if (!check_simulation_stop(data))
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
				philosopher_routine, &data->philosophers[i]))
		{
			printf("Failed to create philosopher thread\n");
			set_simulation_stop(data);
			while (--i >= 0)
				pthread_join(data->philosophers[i].thread_id, NULL);
			return ;
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
		if (pthread_mutex_destroy(&data->philosophers[i].last_meal_mutex))
			printf("Error destroying last_meal for philosopher %d\n", i + 1);
		if (pthread_mutex_destroy(&data->philosophers[i].meals_mutex))
			printf("Error destroying meals_mutex for philosopher %d\n", i + 1);
		if (pthread_mutex_destroy(&data->forks[i].mutex))
			printf("Error destroying fork mutex %d\n", i + 1);
		i++;
	}
	if (pthread_mutex_destroy(&data->stop_mutex))
		printf("Error destroying stop mutex\n");
	if (pthread_mutex_destroy(&data->print_mutex))
		printf("Error destroying print mutex\n");
	if (pthread_mutex_destroy(&data->start_mutex))
		printf("Error destroying start mutex\n");
	if (pthread_mutex_destroy(&data->fork_access_mutex))
		printf("Error destroying fork access mutex\n");
}

static void	handle_single_philosopher(t_data *data)
{
	pthread_mutex_init(&data->philosophers[0].last_meal_mutex, NULL);
	pthread_mutex_init(&data->forks[0].mutex, NULL);
	pthread_mutex_lock(&data->forks[0].mutex);
	print_status(data, 1, "has taken a fork", 0);
	usleep(data->time_death * 1000);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld 1 died\n", get_timestamp_ms() - data->start_time);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->forks[0].mutex);
}
