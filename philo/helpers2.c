/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:03:45 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/03 16:04:11 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	init_fork_mutex(t_desk *d, int i)
{
	if (pthread_mutex_init(&d->forks[i].fork, NULL) != 0)
	{
		d->forks_ini[i] = 0;
		return (1);
	}
	d->forks_ini[i] = 1;
	return (0);
}

static int	init_philo_mutex(t_desk *d, int i)
{
	if (pthread_mutex_init(&d->phls[i].state_mutex, NULL) != 0)
	{
		d->phls_ini[i] = 0;
		return (1);
	}
	d->forks_ini[i] = 1;
	return (0);
}

static void	setup_philo_data(t_desk *d, int i)
{
	d->forks[i].id = i;
	d->phls[i].id = i + 1;
	d->phls[i].meals = 0;
	d->phls[i].done = 0;
	d->phls[i].had_meal_time = d->now;
	d->phls[i].desk = d;
	d->phls[i].left_fork = &d->forks[i];
	d->phls[i].right_fork = &d->forks[(i + 1) % d->philo_amount];
	d->fork_status[i] = 0;
}

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (init_fork_mutex(d, i) != 0)
			return (1);
		if (init_philo_mutex(d, i) != 0)
			return (1);
		setup_philo_data(d, i);
		i++;
	}
	return (0);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->forks = malloc(sizeof(t_fork) * d->philo_amount);
	d->forks_ini = calloc(d->philo_amount, sizeof(int));
	if (!d->forks || !d->forks_ini)
		return (1);
	d->phls = malloc(sizeof(t_philo) * d->philo_amount);
	d->phls_ini = calloc(d->philo_amount, sizeof(int));
	if (!d->phls || !d->phls_ini)
		return (free(d->forks), free(d->forks_ini), 1);
	d->fork_status = malloc(sizeof(int) * d->philo_amount);
	if (!d->fork_status)
	{
		free(d->forks);
		return (free(d->forks_ini), free(d->phls), free(d->phls_ini), 1);
	}
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0
		|| pthread_mutex_init(&d->write_mutex, NULL) != 0
		|| pthread_mutex_init(&d->butler_mutex, NULL) != 0)
	{
		free(d->forks);
		free(d->fork_status);
		return (free(d->forks_ini), free(d->phls), free(d->phls_ini), 1);
	}
	return (setup_philos_and_forks(d));
}
