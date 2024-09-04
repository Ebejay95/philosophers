/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:51:02 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/03 21:23:12 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	screening(t_desk *d, int *all_ate, int i)
{
	long long	time_since_meal;

	pthread_mutex_lock(&d->phls[i].state_mutex);
	time_since_meal = my_now() - d->phls[i].had_meal_time;
	if (time_since_meal > d->die_time)
	{
		set_end(d);
		log_action(&d->phls[i], "died");
		pthread_mutex_unlock(&d->phls[i].state_mutex);
		return (1);
	}
	if (d->meal_amount != -1 && d->phls[i].meals < d->meal_amount)
		*all_ate = 0;
	pthread_mutex_unlock(&d->phls[i].state_mutex);
	return (0);
}

void	*run_monitor(void *d_point)
{
	t_desk		*d;
	int			i;
	int			all_ate;

	d = (t_desk *)d_point;
	while (1)
	{
		all_ate = 1;
		i = 0;
		while (i < d->philo_amount)
		{
			if (screening(d, &all_ate, i))
				return (NULL);
			i++;
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
