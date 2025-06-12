/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:35:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/12 12:22:45 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&philo->data->forks[first_fork].mutex);
	if (philo->data->forks[first_fork].is_taken
		|| check_simulation_stop(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork].mutex);
		return (0);
	}
	philo->data->forks[first_fork].is_taken = 1;
	pthread_mutex_lock(&philo->data->forks[second_fork].mutex);
	if (philo->data->forks[second_fork].is_taken
		|| check_simulation_stop(philo->data))
	{
		philo->data->forks[first_fork].is_taken = 0;
		pthread_mutex_unlock(&philo->data->forks[second_fork].mutex);
		pthread_mutex_unlock(&philo->data->forks[first_fork].mutex);
		return (0);
	}
	philo->data->forks[second_fork].is_taken = 1;
	print_status(philo->data, philo->id, "has taken a fork", 0);
	print_status(philo->data, philo->id, "has taken a fork", 0);
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
	int	first_fork;
	int	second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	philo->data->forks[first_fork].is_taken = 0;
	philo->data->forks[second_fork].is_taken = 0;
	pthread_mutex_unlock(&philo->data->forks[second_fork].mutex);
	pthread_mutex_unlock(&philo->data->forks[first_fork].mutex);
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
	int	think_time;

	print_status(philo->data, philo->id, "is thinking", 0);
	if (philo->data->nb_philo % 2 != 0)
	{
		think_time = (philo->data->time_eat * 2 - philo->data->time_sleep);
		ft_usleep(think_time, philo->data);
	}
}
