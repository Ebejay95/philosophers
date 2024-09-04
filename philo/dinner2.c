/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:32:44 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/04 07:05:16 by jeberle          ###   ########.fr       */
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
		usleep(100);
		if (should_exit(d))
			break ;
	}
}

void	calculate_think_time(t_philo *p, long long *think_time)
{
	long long	eat_sleep_time;
	long long	cycle_time;

	eat_sleep_time = p->desk->eat_time + p->desk->sleep_time;
	cycle_time = eat_sleep_time * 2;
	if (cycle_time >= p->desk->die_time)
		*think_time = (p->desk->die_time - p->desk->eat_time) / 2;
	else
		*think_time = (p->desk->die_time - eat_sleep_time) / 2;
	if (*think_time < 0)
		*think_time = 0;
	else if (*think_time > p->desk->die_time / 4)
		*think_time = p->desk->die_time / 4;
}

void	think_in_start(t_philo *p)
{
	log_action(p, "is thinking");
	precise_sleep(p->desk->eat_time, p->desk);
	p->desk->first_iteration = 0;
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
