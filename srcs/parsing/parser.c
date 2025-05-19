/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:59:21 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 15:24:48 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_philosophers(t_data *data);

void	parse_input(char **av, t_data *data, struct timeval *tv)
{
	data->nb_eat = -1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_death = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_eat = ft_atoi(av[5]);
	gettimeofday(tv, NULL);
	data->start_time = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	init_philosophers(data);
}

static void	init_philosophers(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < MAX_PHILO)
	{
		if (i < data->nb_philo)
		{
			data->philosophers[i].id = i;
			data->philosophers[i].state = THINKING; 
		}
		i++;
	}
}
