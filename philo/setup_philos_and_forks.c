/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos_and_forks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:03:45 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 16:27:26 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	init_fork_mutex(t_desk *d, int i)
{
	if (pthread_mutex_init(&d->forks[i], NULL) != 0)
		return (1);
	return (0);
}

static int	init_philo_mutex(t_desk *d, int i)
{
	if (pthread_mutex_init(&d->phls[i].state_mutex, NULL) != 0)
	{
		d->phls_ini[i] = 0;
		return (1);
	}
	d->phls_ini[i] = 1;
	return (0);
}

static void	setup_philo_data(t_desk *d, int i)
{
	d->phls[i].id = i + 1;
	d->phls[i].meals = 0;
	d->phls[i].done = 0;
	d->phls[i].had_meal_time = d->now;
	d->phls[i].desk = d;
	d->phls[i].left_fork = NULL;
	d->phls[i].right_fork = NULL;
}

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	d->forks = malloc(sizeof(pthread_mutex_t) * d->philo_amount);
	if (!d->forks)
		return (1);
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
