/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:35:26 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/12 10:19:13 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		has_forks;
	int		i;

	i = 0;
	has_forks = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	if (check_simulation_stop(data))
		return (NULL);
	sync_philo_routine(data, philo);
	update_last_meal(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_simulation_stop(data))
	{
		if (!philo_cycle(philo, &has_forks, i))
			break ;
		i++;
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
		pthread_mutex_lock(&data->philosophers[i].meals_mutex);
		if ((data->philosophers[i].meals_eaten < data->nb_eat)
			&& data->nb_eat != -1)
		{
			all_full = 0;
		}
		pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
		i++;
	}
	if (data->nb_eat != -1 && all_full)
	{
		set_simulation_stop(data);
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
	if (check_simulation_stop(data))
		return (NULL);
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
		usleep(100);
	}
}
