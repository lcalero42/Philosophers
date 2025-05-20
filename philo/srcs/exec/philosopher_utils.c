/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:33:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 13:34:28 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status, int should_print)
{
	pthread_mutex_lock(&data->print_mutex);
	if (!check_simulation_stop(data) || should_print)
		printf("%lld %d %s\n",
			get_timestamp_ms() - data->start_time, id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_simulation_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
