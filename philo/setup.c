/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:35:47 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/11 15:31:50 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	initialize_mutexes(t_desk *d)
{
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0
		|| pthread_mutex_init(&d->write_mutex, NULL) != 0
		|| pthread_mutex_init(&d->monitor_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->monitor_should_exit = 0;
	if (initialize_mutexes(d) != 0)
		return (1);
	return (setup_philos_and_forks(d));
}
