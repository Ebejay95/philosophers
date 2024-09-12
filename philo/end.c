/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:47:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/12 10:26:05 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_end(t_desk *d)
{
	int	end;

	pthread_mutex_lock(&d->end_mutex);
	end = d->end;
	pthread_mutex_unlock(&d->end_mutex);
	return (end);
}

void	set_end(t_desk *d)
{
	pthread_mutex_lock(&d->end_mutex);
	d->end = 1;
	pthread_mutex_unlock(&d->end_mutex);
}

void	wait_for_threads(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (d->phls[i].thread != 0)
		{
			pthread_join(d->phls[i].thread, NULL);
			d->phls[i].thread = 0;
		}
		i++;
	}
}

int	end(t_desk *d)
{
	int	i;

	set_end(d);
	wait_for_threads(d);
	if (d->monitor != 0)
	{
		pthread_mutex_lock(&d->monitor_mutex);
		d->monitor_should_exit = 1;
		pthread_mutex_unlock(&d->monitor_mutex);
		pthread_join(d->monitor, NULL);
		d->monitor = 0;
	}
	i = 0;
	while (i < d->philo_amount)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->phls[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&d->end_mutex);
	pthread_mutex_destroy(&d->write_mutex);
	pthread_mutex_destroy(&d->monitor_mutex);
	pthread_mutex_destroy(&d->flag_mutex);
	return (0);
}
