/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:32:44 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 15:18:14 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	precise_sleep(long long time, t_desk *d)
{
	long long	start;
	long long	now;

	start = my_now();
	while (!should_exit(d))
	{
		now = my_now();
		if (now - start >= time)
			break ;
		usleep(500);
		if (should_exit(d))
			break ;
	}
}

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
