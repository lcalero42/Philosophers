/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:39:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/19 20:01:20 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>

static const char *get_state_string(t_state state)
{
	if (state == THINKING)
		return "THINKING";
	if (state == SLEEPING)
		return "SLEEPING";
	if (state == EATING)
		return "EATING";
	return "UNKNOWN";
}

void	print_data(t_data *data)
{
	int	i;

	printf("\n========== SIMULATION SETTINGS ==========\n");
	printf("Number of philosophers : %d\n", data->nb_philo);
	printf("Start time             : %lld ms\n", data->start_time);
	printf("Time to die            : %d ms\n", data->time_death);
	printf("Time to eat            : %d ms\n", data->time_eat);
	printf("Time to sleep          : %d ms\n", data->time_sleep);
	if (data->nb_eat != -1)
		printf("Number of times to eat : %d\n", data->nb_eat);
	else
		printf("Number of times to eat : Unlimited\n");

	printf("\n========== PHILOSOPHER DATA ==========\n");
	for (i = 0; i < data->nb_philo; i++)
	{
		t_philo *philo = &data->philosophers[i];

		printf("\nPhilosopher #%d\n", philo->id);
		printf("  Left fork ID        : %d\n", philo->left_fork_id);
		printf("  Right fork ID       : %d\n", philo->right_fork_id);
		printf("  State               : %s\n", get_state_string(philo->state));
		printf("  Last meal time      : %lld ms\n", philo->last_meal);
		printf("  Meals eaten         : %d\n", philo->meals_eaten);
		printf("  Thread ID           : %lu\n", (unsigned long)philo->thread_id);
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
	//print_data(&data);
	exec(&data);
	return (0);
}
