/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:42:40 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/04 14:03:17 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_limit_reached(t_philo *philo)
{
	int	reached_limit;

	pthread_mutex_lock(&philo->meals_mutex);
	reached_limit = (philo->data->nb_eat != -1
			&& philo->meals_eaten >= philo->data->nb_eat);
	pthread_mutex_unlock(&philo->meals_mutex);
	return (reached_limit);
}

void	ret_error(t_data *data, const char *error_mess)
{
	perror(error_mess);
	set_simulation_stop(data);
	join_threads(data);
	cleanup(data);
}
