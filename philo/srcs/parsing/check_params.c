/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:14:30 by lcalero           #+#    #+#             */
/*   Updated: 2025/06/11 18:21:02 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_input(char **av, int ac);
static int	ft_isdigit(char a);

int	check_params(t_data *data, int ac, char **av)
{
	if (!check_input(av, ac))
		return (0);
	if (data->nb_philo < 1)
	{
		printf("number of philosopher must be at least one\n");
		return (0);
	}
	if (data->nb_philo > MAX_PHILO)
	{
		printf("number of philosopher must not be above %i\n", MAX_PHILO);
		return (0);
	}
	if (data->time_eat < 1 || data->time_sleep < 1 || data->time_death < 1)
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

static int	check_input(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("parameters must not contain characters\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_isdigit(char a)
{
	return (a >= '0' && a <= '9');
}
