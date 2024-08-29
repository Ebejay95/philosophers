/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:47:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/29 21:13:54 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (pthread_mutex_init(&d->forks[i].fork, NULL) != 0)
			return (1);
		d->forks[i].id = i;
		d->philos[i].id = i + 1;
		d->philos[i].meals = 0;
		d->philos[i].done = 0;
		d->philos[i].had_meal_time = d->now;
		d->philos[i].desk = d;
		d->philos[i].left_fork = &d->forks[i];
		d->philos[i].right_fork = &d->forks[(i + 1) % d->philo_amount];
		i++;
	}
	return (0);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->forks = malloc(sizeof(t_fork) * d->philo_amount);
	if (!d->forks)
		return (1);
	d->philos = malloc(sizeof(t_philo) * d->philo_amount);
	if (!d->philos)
	{
		free(d->forks);
		return (1);
	}
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0)
		return (1);
	setup_philos_and_forks(d);
	return (0);
}

int	end(t_desk *d)
{
	int	i;

	pthread_join(d->monitor, NULL);
	i = 0;
	while (i < d->philo_amount)
	{
		pthread_join(d->philos[i].thread, NULL);
		pthread_mutex_destroy(&d->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&d->end_mutex);
	free(d->philos);
	free(d->forks);
	return (0);
}
