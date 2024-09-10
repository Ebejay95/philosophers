/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:35:25 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/10 14:59:06 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	handle_single_philosopher(t_philo *p)
{
	log_action(p, "has taken a fork");
	precise_sleep(p->desk->die_time, p->desk);
}

int	should_exit(t_desk *d)
{
	int	result;

	pthread_mutex_lock(&d->end_mutex);
	result = d->end;
	pthread_mutex_unlock(&d->end_mutex);
	return (result);
}

void	start_trick(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		log_action(p, "is thinking");
	}
	else
	{
		usleep(500);
		log_action(p, "is thinking");
	}
}

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
		usleep(1000);
		if (should_exit(d))
			break ;
	}
}
