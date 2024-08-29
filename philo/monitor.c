/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:51:02 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/29 21:57:10 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*run_monitor(void *d_point)
{
	t_desk	*d;
	int		i;
	int		all_ate;

	d = (t_desk *)d_point;
	while (1)
	{
		pthread_mutex_lock(&d->end_mutex);
		if (d->end)
		{
			pthread_mutex_unlock(&d->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&d->end_mutex);
		all_ate = 1;
		i = 0;
		while (i < d->philo_amount)
		{
			if (current_time_in_milliseconds() - d->philos[i].had_meal_time > d->die_time)
			{
				printf(RED"%lld %d died\n"D, current_time_in_milliseconds() - d->now, d->philos[i].id);
				pthread_mutex_lock(&d->end_mutex);
				d->end = 1;
				pthread_mutex_unlock(&d->end_mutex);
				return (NULL);
			}
			if (d->meal_amount != -1 && d->philos[i].meals < d->meal_amount)
				all_ate = 0;
		}
		if (d->meal_amount != -1 && all_ate)
		{
			pthread_mutex_lock(&d->end_mutex);
			d->end = 1;
			pthread_mutex_unlock(&d->end_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
