/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:55:21 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/11 15:41:44 by jeberle          ###   ########.fr       */
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
	precise_sleep(p->eat_time, p->desk);
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
	{
		p->done = 1;
	}
	pthread_mutex_unlock(&p->state_mutex);
	return (0);
}
