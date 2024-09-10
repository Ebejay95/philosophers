/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:35:47 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/10 14:59:12 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	allocate_philosophers(t_desk *d)
{
	d->phls = malloc(sizeof(t_philo) * d->philo_amount);
	if (!d->phls)
		return (1);
	d->phls_ini = malloc(d->philo_amount * sizeof(int));
	if (!d->phls_ini)
	{
		free(d->phls_ini);
		return (1);
	}
	return (0);
}

static int	initialize_mutexes(t_desk *d)
{
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0
		|| pthread_mutex_init(&d->write_mutex, NULL) != 0)
		return (1);
	return (0);
}

static void	cleanup_on_error(t_desk *d)
{
	free(d->phls);
	free(d->phls_ini);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->monitor_should_exit = 0;
	if (allocate_philosophers(d) != 0)
		return (1);
	if (initialize_mutexes(d) != 0)
	{
		cleanup_on_error(d);
		return (1);
	}
	if (pthread_mutex_init(&d->monitor_mutex, NULL) != 0)
	{
		cleanup_on_error(d);
		return (1);
	}
	return (setup_philos_and_forks(d));
}
