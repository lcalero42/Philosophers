/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:35:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 13:29:15 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork_id].mutex);
	print_status(data, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&data->forks[philo->right_fork_id].mutex);
	print_status(data, philo->id, "has taken a fork", 0);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	update_last_meal(philo);
	print_status(data, philo->id, "is eating", 0);
	usleep(data->time_eat * 1000);
	philo->meals_eaten++;
}

void	put_down_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->right_fork_id].mutex);
	pthread_mutex_unlock(&data->forks[philo->left_fork_id].mutex);
}

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(data, philo->id, "is sleeping", 0);
	usleep(data->time_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_status(philo->data, philo->id, "is thinking", 0);
}
