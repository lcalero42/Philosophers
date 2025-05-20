/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:14:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 15:31:32 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_params(t_data *data, int ac)
{
	if (data->nb_philo < 1)
	{
		printf("number of philosopher must be at least one\n");
		return (0);
	}
	if (data->nb_philo > 250)
	{
		printf("number of philosopher must not be above 250\n");
		return (0);
	}
	if (data->time_eat < 0 || data->time_sleep < 0 || data->time_death < 0)
	{
		printf("timers must be over 0\n");
		return (0);
	}
	if (ac == 6 && data->nb_eat < 0)
	{
		printf("number of meals to eat must be 0 or above\n");
		return (0);
	}
	return (1);
}
