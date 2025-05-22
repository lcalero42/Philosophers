/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:35:26 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/22 18:53:55 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	sync_philo_routine(data, philo);
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!check_simulation_stop(data))
	{
		take_forks(philo);
		if (check_simulation_stop(data))
		{
			put_down_forks(philo);
			break ;
		}
		eat(philo);
		put_down_forks(philo);
		if (check_simulation_stop(data))
			break ;
		philo_sleep(philo);
		if (check_simulation_stop(data))
			break ;
		think(philo);
	}
	return (NULL);
}

int	check_philosopher_death(t_data *data, int i)
{
	long long	now;
	int			is_dead;

	now = get_timestamp_ms();
	is_dead = 0;
	pthread_mutex_lock(&data->philosophers[i].last_meal_mutex);
	if (now - data->philosophers[i].last_meal >= data->time_death)
	{
		pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
		set_simulation_stop(data);
		print_status(data, data->philosophers[i].id, "died", 1);
		is_dead = 1;
	}
	else
		pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
	return (is_dead);
}

int	check_all_philosophers_full(t_data *data)
{
	int	i;
	int	all_full;

	i = 0;
	all_full = 1;
	while (i < data->nb_philo && all_full)
	{
		pthread_mutex_lock(&data->philosophers[i].last_meal_mutex);
		if ((data->philosophers[i].meals_eaten < data->nb_eat)
			&& data->nb_eat != -1)
			all_full = 0;
		pthread_mutex_unlock(&data->philosophers[i].last_meal_mutex);
		i++;
	}
	if (data->nb_eat != -1 && all_full)
	{
		set_simulation_stop(data);
		pthread_mutex_lock(&data->print_mutex);
		printf("ALL MEALS HAVE BEEN EATEN\n");
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	sync_monitor_routine(data);
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_philosophers_full(data))
			return (NULL);
		usleep(500);
	}
}
