/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:42:40 by lcalero           #+#    #+#             */
/*   Updated: 2025/05/20 13:44:20 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ret_error(t_data *data, const char *error_mess)
{
	perror(error_mess);
	set_simulation_stop(data);
	join_threads(data);
	cleanup(data);
	exit(EXIT_FAILURE);
}
