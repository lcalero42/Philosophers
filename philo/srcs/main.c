/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:39:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 13:17:56 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	struct timeval	tv;
	t_data			data;

	if (ac != 5 && ac != 6)
		return (1);
	parse_input(av, &data, &tv);
	exec(&data);
	return (0);
}
