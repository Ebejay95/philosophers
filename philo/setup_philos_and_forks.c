/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos_and_forks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:03:45 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/11 10:47:14 by jeberle          ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

static void	setup_philo_data(t_desk *d, int i)
{
	d->phls[i].id = i + 1;
	d->phls[i].meals = 0;
	d->phls[i].done = 0;
	d->phls[i].had_meal_time = d->now;
	d->phls[i].desk = d;
	d->phls[i].left_fork = &d->forks[i];
	d->phls[i].right_fork = &d->forks[(i + 1) % d->philo_amount];
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
