/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:35:25 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 15:18:44 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	eat(t_philo *p)
{
	log_action(p, "is eating");
	pthread_mutex_lock(&p->state_mutex);
	p->had_meal_time = my_now();
	pthread_mutex_unlock(&p->state_mutex);
	if (should_exit(p->desk))
		return (1);
	precise_sleep(p->desk->eat_time, p->desk);
	if (should_exit(p->desk))
		return (1);
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
	{
		p->done = 1;
	}
	pthread_mutex_unlock(&p->state_mutex);
	return (0);
}

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
		usleep(100);
		log_action(p, "is thinking");
	}
}
