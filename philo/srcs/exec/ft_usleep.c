/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:48:10 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/22 18:55:36 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time, t_data *data)
{
	long long	start;
	long long	elapsed;

	start = get_timestamp_ms();
	while (!check_simulation_stop(data))
	{
		elapsed = get_timestamp_ms() - start;
		if (elapsed >= time)
			break ;
		usleep(100);
	}
}
