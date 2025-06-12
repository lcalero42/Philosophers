/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:59:26 by luis              #+#    #+#             */
/*   Updated: 2025/06/12 10:18:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philo_cycle(t_philo *philo, int *has_forks, int i)
{
	if (i == 0)
		print_status(philo->data, philo->id, "is thinking", 0);
	take_forks(philo);
	if (check_simulation_stop(philo->data))
	{
		if (*has_forks)
			put_down_forks(philo);
		return (0);
	}
	*has_forks = 1;
	if (check_limit_reached(philo))
	{
		put_down_forks(philo);
		return (0);
	}
	eat(philo);
	put_down_forks(philo);
	*has_forks = 0;
	if (check_simulation_stop(philo->data) || check_limit_reached(philo))
		return (0);
	philo_sleep(philo);
	if (check_simulation_stop(philo->data))
		return (0);
	think(philo);
	return (!check_simulation_stop(philo->data));
}

int	acquire_fork(t_data *data, int fork_id, int philo_id)
{
	pthread_mutex_lock(&data->forks[fork_id].mutex);
	data->forks[fork_id].is_taken = 1;
	if (check_simulation_stop(data))
	{
		data->forks[fork_id].is_taken = 0;
		pthread_mutex_unlock(&data->forks[fork_id].mutex);
		return (0);
	}
	print_status(data, philo_id, "has taken a fork", 0);
	return (1);
}

void	release_forks(t_data *data, int first_fork, int second_fork)
{
	data->forks[second_fork].is_taken = 0;
	data->forks[first_fork].is_taken = 0;
	pthread_mutex_unlock(&data->forks[second_fork].mutex);
	pthread_mutex_unlock(&data->forks[first_fork].mutex);
}

void	get_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork_id;
		*second = philo->left_fork_id;
	}
	else
	{
		*first = philo->left_fork_id;
		*second = philo->right_fork_id;
	}
}

void	check_meals(int local_meals, t_data *data)
{
	int		all_full;
	int		i;

	if (data->nb_eat != -1 && local_meals == data->nb_eat)
	{
		all_full = 1;
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philosophers[i].meals_mutex);
			if (data->philosophers[i].meals_eaten < data->nb_eat)
				all_full = 0;
			pthread_mutex_unlock(&data->philosophers[i].meals_mutex);
			i++;
		}
		if (all_full)
			set_simulation_stop(data);
	}
}
