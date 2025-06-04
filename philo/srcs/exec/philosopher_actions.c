/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:35:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/04 14:19:05 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_forks(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	pthread_mutex_lock(&data->fork_access_mutex);
	get_fork_order(philo, &first_fork, &second_fork);
	if (!acquire_fork(data, first_fork, philo->id)
		|| !acquire_fork(data, second_fork, philo->id))
	{
		if (data->forks[first_fork].is_taken)
		{
			data->forks[first_fork].is_taken = 0;
			pthread_mutex_unlock(&data->forks[first_fork].mutex);
		}
		pthread_mutex_unlock(&data->fork_access_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->fork_access_mutex);
	return (1);
}

void	eat(t_philo *philo)
{
	t_data	*data;
	int		local_meals_eaten;

	data = philo->data;
	update_last_meal(philo);
	print_status(data, philo->id, "is eating", 0);
	ft_usleep(data->time_eat, data);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	local_meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_mutex);
	check_meals(local_meals_eaten, data);
}

void	put_down_forks(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork_id;
		second_fork = philo->left_fork_id;
	}
	else
	{
		first_fork = philo->left_fork_id;
		second_fork = philo->right_fork_id;
	}
	data->forks[second_fork].is_taken = 0;
	pthread_mutex_unlock(&data->forks[second_fork].mutex);
	data->forks[first_fork].is_taken = 0;
	pthread_mutex_unlock(&data->forks[first_fork].mutex);
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(data, philo->id, "is sleeping", 0);
	ft_usleep(data->time_sleep, data);
}

void	think(t_philo *philo)
{
	print_status(philo->data, philo->id, "is thinking", 0);
	if (philo->id % 2 != 0 && philo->data->time_eat >= philo->data->time_sleep)
		ft_usleep(philo->data->time_eat - philo->data->time_sleep + 1,
			philo->data);
}
