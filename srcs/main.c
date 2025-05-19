/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:39:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 15:19:53 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_data(t_data *data)
{
	int	i;
	
	i = 0;
	printf("NUMBER OF PHILOSPOPHER : %d\n", data->nb_philo);
	printf("START TIME : %lld\n", data->start_time);
	printf("TIME TO DIE : %d\n", data->time_death);
	printf("TIME TO EAT : %d\n", data->time_eat);
	printf("TIME TO SLEEP : %d\n", data->time_sleep);
	printf("-----PHILOSOPHERS-----\n");
	while (i < data->nb_philo)
	{
		printf("PHILO ID : %d\n", data->philosophers[i].id);
		printf("PHILO STATE : %d\n", data->philosophers[i].state);
		i++;
	}
}

int	main(int ac, char **av)
{
	struct timeval	tv;
	t_data			data;

	if (ac != 5 && ac != 6)
		return (1);
	printf("Philosopher launched\n");
	parse_input(av, &data, &tv);
	print_data(&data);
	return (0);
}
