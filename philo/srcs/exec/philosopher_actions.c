/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:35:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/27 20:52:17 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_forks(t_philo *philo)  // Change return type to int
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (philo->left_fork_id < philo->right_fork_id)
	{
		first_fork = philo->left_fork_id;
		second_fork = philo->right_fork_id;
	}
	else
	{
		first_fork = philo->right_fork_id;
		second_fork = philo->left_fork_id;
	}
	pthread_mutex_lock(&data->forks[first_fork].mutex);
	data->forks[first_fork].is_taken = 1;
	if (check_simulation_stop(data))
	{
		data->forks[first_fork].is_taken = 0;
		pthread_mutex_unlock(&data->forks[first_fork].mutex);
		return (0);  // Failed to acquire both forks
	}
	print_status(data, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&data->forks[second_fork].mutex);
	data->forks[second_fork].is_taken = 1;
	if (check_simulation_stop(data))
	{
		data->forks[second_fork].is_taken = 0;
		data->forks[first_fork].is_taken = 0;
		pthread_mutex_unlock(&data->forks[second_fork].mutex);
		pthread_mutex_unlock(&data->forks[first_fork].mutex);
		return (0);  // Failed to acquire both forks
	}
	print_status(data, philo->id, "has taken a fork", 0);
	return (1);  // Successfully acquired both forks
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	update_last_meal(philo);
	print_status(data, philo->id, "is eating", 0);
	ft_usleep(data->time_eat, philo->data);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
}

void	put_down_forks(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	if (philo->left_fork_id < philo->right_fork_id)
	{
		first_fork = philo->left_fork_id;
		second_fork = philo->right_fork_id;
	}
	else
	{
		first_fork = philo->right_fork_id;
		second_fork = philo->left_fork_id;
	}
	// Release in reverse order (second fork first)
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
}
