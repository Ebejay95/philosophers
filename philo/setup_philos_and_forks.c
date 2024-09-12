/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos_and_forks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:03:45 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/12 11:15:59 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	setup_philo_data(t_desk *d, int i)
{
	d->phls[i].id = i + 1;
	d->phls[i].meals = 0;
	d->phls[i].done = 0;
	d->phls[i].eat_time = d->eat_time;
	d->phls[i].die_time = d->die_time;
	d->phls[i].had_meal_time = d->now;
	d->phls[i].desk = d;
	d->phls[i].left_fork = &d->forks[i];
	d->phls[i].right_fork = &d->forks[(i + 1) % d->philo_amount];
	d->phls[i].first_think = 1;
}

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			return (1);
		if (pthread_mutex_init(&d->phls[i].state_mutex, NULL) != 0)
			return (1);
		setup_philo_data(d, i);
		i++;
	}
	return (0);
}
