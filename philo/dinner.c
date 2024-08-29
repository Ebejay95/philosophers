/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/29 21:59:14 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*run_philosopher(void *p_point)
{
	t_philo	*p;

	p = (t_philo *)p_point;
	while (1)
	{
		pthread_mutex_lock(&p->desk->end_mutex);
		if (p->desk->end)
		{
			pthread_mutex_unlock(&p->desk->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->desk->end_mutex);
		pthread_mutex_lock(&p->left_fork->fork);
		printf(G"%lld %d has taken a fork\n"D, current_time_in_milliseconds() - p->desk->now, p->id);
		pthread_mutex_lock(&p->right_fork->fork);
		printf(G"%lld %d has taken a fork\n"D, current_time_in_milliseconds() - p->desk->now, p->id);
		printf(Y"%lld %d is eating\n"D, current_time_in_milliseconds() - p->desk->now, p->id);
		p->had_meal_time = current_time_in_milliseconds();
		usleep(p->desk->eat_time * 1000);
		p->meals++;
		if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
			p->done = 1;
		pthread_mutex_unlock(&p->left_fork->fork);
		pthread_mutex_unlock(&p->right_fork->fork);
		printf(B"%lld %d is sleeping\n"D, current_time_in_milliseconds() - p->desk->now, p->id);
		usleep(p->desk->sleep_time * 1000);
		printf(M"%lld %d is thinking\n"D, current_time_in_milliseconds() - p->desk->now, p->id);
	}
	return (NULL);
}
