/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:47:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/09 16:28:04 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	wait_for_threads(t_desk *d)
{
	int	i;

	if (d->monitor != 0)
		pthread_join(d->monitor, NULL);
	i = 0;
	while (i < d->philo_amount)
	{
		if (d->phls[i].thread != 0)
			pthread_join(d->phls[i].thread, NULL);
		i++;
	}
}

void	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	int	err;

	err = pthread_mutex_lock(mutex);
	if (err == 0)
	{
		pthread_mutex_unlock(mutex);
		pthread_mutex_destroy(mutex);
	}
	else if (err == 1)
	{
		pthread_mutex_destroy(mutex);
	}
}

int	end(t_desk *d)
{
	int	i;

	wait_for_threads(d);
	i = 0;
	while (i < d->philo_amount)
	{
		safe_mutex_destroy(&d->forks[i]);
		if (d->phls_ini && d->phls_ini[i])
			safe_mutex_destroy(&d->phls[i].state_mutex);
		i++;
	}
	safe_mutex_destroy(&d->end_mutex);
	safe_mutex_destroy(&d->write_mutex);
	free(d->phls);
	free(d->forks);
	return (0);
}
