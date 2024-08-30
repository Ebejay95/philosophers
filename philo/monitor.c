/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:51:02 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/30 10:02:01 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*run_monitor(void *d_point)
{
	t_desk		*d;
	int			i;
	int			all_ate;
	long long	time_since_meal;

	d = (t_desk *)d_point;
	while (1)
	{
		all_ate = 1;
		i = -1;
		while (++i < d->philo_amount)
		{
			pthread_mutex_lock(&d->philos[i].state_mutex);
			time_since_meal = current_time_in_milliseconds() - d->philos[i].had_meal_time;
			if (time_since_meal > d->die_time)
			{
				log_action(&d->philos[i], "died", RED);
				set_end(d);
				pthread_mutex_unlock(&d->philos[i].state_mutex);
				return (NULL);
			}
			if (d->meal_amount != -1 && d->philos[i].meals < d->meal_amount)
				all_ate = 0;
			pthread_mutex_unlock(&d->philos[i].state_mutex);
		}
		if (d->meal_amount != -1 && all_ate)
		{
			set_end(d);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
