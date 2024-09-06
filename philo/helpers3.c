/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:35:47 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/06 21:25:07 by jeberle          ###   ########.fr       */
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

// static int	allocate_fork_state(t_desk *d)
// {
// 	d->fstate = malloc(sizeof(int) * d->philo_amount);
// 	if (!d->fstate)
// 		return (1);
// 	return (0);
// }

static int	initialize_mutexes(t_desk *d)
{
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0
		|| pthread_mutex_init(&d->write_mutex, NULL) != 0
		|| pthread_mutex_init(&d->butler_mutex, NULL) != 0
		|| pthread_mutex_init(&d->first_iteration_mutex, NULL) != 0)
		return (1);
	return (0);
}

static void	cleanup_on_error(t_desk *d)
{
	free(d->forks);
	free(d->forks_ini);
	free(d->phls);
	free(d->phls_ini);
	//free(d->fstate);
}

int	setup(t_desk *d)
{
	d->end = 0;
	if (allocate_forks(d) != 0)
		return (1);
	if (allocate_philosophers(d) != 0)
	{
		free(d->forks);
		free(d->forks_ini);
		return (1);
	}
	// if (allocate_fork_state(d) != 0)
	// {
	// 	free(d->forks);
	// 	free(d->forks_ini);
	// 	free(d->phls);
	// 	free(d->phls_ini);
	// 	return (1);
	// }
	if (initialize_mutexes(d) != 0)
	{
		cleanup_on_error(d);
		return (1);
	}
	return (setup_philos_and_forks(d));
}
