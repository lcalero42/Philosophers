/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:59:26 by luis              #+#    #+#             */
/*   Updated: 2025/06/03 11:43:50 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philo_cycle(t_philo *philo, int *has_forks)
{
	take_forks(philo);
	if (check_simulation_stop(philo->data))
	{
		if (*has_forks)
			put_down_forks(philo);
		return (0);
	}
	*has_forks = 1;
	pthread_mutex_lock(&philo->meals_mutex);
	if (philo->data->nb_eat != -1 && philo->meals_eaten >= philo->data->nb_eat)
	{
		pthread_mutex_unlock(&philo->meals_mutex);
		put_down_forks(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->meals_mutex);
	eat(philo);
	put_down_forks(philo);
	*has_forks = 0;
	if (check_simulation_stop(philo->data))
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
