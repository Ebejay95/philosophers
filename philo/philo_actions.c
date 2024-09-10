/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:55:21 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/10 14:59:00 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	eat(t_philo *p)
{
	long long	start_time;

	start_time = my_now();
	log_action(p, "is eating");
	pthread_mutex_lock(&p->state_mutex);
	p->had_meal_time = start_time;
	pthread_mutex_unlock(&p->state_mutex);
	while (my_now() - start_time < p->desk->eat_time)
	{
		if (should_exit(p->desk))
			return (1);
		usleep(100);
	}
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
	{
		p->done = 1;
	}
	pthread_mutex_unlock(&p->state_mutex);
	return (0);
}
