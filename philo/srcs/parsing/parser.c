/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:59:21 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 15:29:26 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_philosophers(t_data *data);
static void	init_forks(t_data *data);

void	parse_input(char **av, t_data *data, struct timeval *tv, int ac)
{
	memset(data, 0, sizeof(t_data));
	data->nb_eat = -1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_death = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_eat = ft_atoi(av[5]);
	if (!check_params(data, ac))
		return ;
	gettimeofday(tv, NULL);
	data->start_time = tv->tv_sec * 1000 + tv->tv_usec / 1000;
	init_philosophers(data);
	init_forks(data);
}

static void	init_philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = &data->philosophers[i];
		philo->id = i + 1;
		philo->left_fork_id = i;
		philo->right_fork_id = (i + 1) % data->nb_philo;
		philo->last_meal = data->start_time;
		philo->meals_eaten = 0;
		philo->data = data;
		if (pthread_mutex_init(&philo->last_meal_mutex, NULL))
			ret_error(data, "Failed to init mutex\n");
		i++;
	}
}

static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
			ret_error(data, "Failed to init mutex\n");
		i++;
	}
}
