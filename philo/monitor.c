/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:51:02 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/11 16:19:20 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_philosopher_state(t_desk *d, int i, int *all_ate)
{
	pthread_mutex_lock(&d->phls[i].state_mutex);
	if (my_now() - d->phls[i].had_meal_time > d->die_time)
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

int	check_exit_condition(t_desk *d)
{
	pthread_mutex_lock(&d->monitor_mutex);
	if (d->monitor_should_exit)
	{
		pthread_mutex_unlock(&d->monitor_mutex);
		return (1);
	}
	pthread_mutex_unlock(&d->monitor_mutex);
	return (0);
}

int	check_philosophers(t_desk *d)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	i = 0;
	while (i < d->philo_amount)
	{
		if (check_philosopher_state(d, i, &all_ate))
			return (1);
		i++;
	}
	if (d->meal_amount != -1 && all_ate)
	{
		set_end(d);
		return (1);
	}
	return (0);
}

void	*run_monitor(void *d_point)
{
	t_desk	*d;

	d = (t_desk *)d_point;
	while (1)
	{
		if (check_exit_condition(d))
			break ;
		if (check_philosophers(d))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
