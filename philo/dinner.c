/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/30 10:08:49 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

int	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->right_fork->fork);
		log_action(p, "has taken a fork", G);
		pthread_mutex_lock(&p->left_fork->fork);
		log_action(p, "has taken a fork", G);
	}
	else
	{
		pthread_mutex_lock(&p->left_fork->fork);
		log_action(p, "has taken a fork", G);
		pthread_mutex_lock(&p->right_fork->fork);
		log_action(p, "has taken a fork", G);
	}
	return (0);
}

int	eat(t_philo *p)
{
	log_action(p, "is eating", Y);
	pthread_mutex_lock(&p->state_mutex);
	p->had_meal_time = current_time_in_milliseconds();
	pthread_mutex_unlock(&p->state_mutex);
	usleep(p->desk->eat_time * 1000);
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
		p->done = 1;
	pthread_mutex_unlock(&p->state_mutex);
	pthread_mutex_unlock(&p->right_fork->fork);
	pthread_mutex_unlock(&p->left_fork->fork);
	return (0);
}

int	sleep_and_think(t_philo *p)
{
	log_action(p, "is sleeping", B);
	usleep(p->desk->sleep_time * 1000);
	log_action(p, "is thinking", M);
	return (0);
}

void	*run_philosopher(void *p_point)
{
	t_philo	*p;

	p = (t_philo *)p_point;
	while (1)
	{
		if (check_end(p->desk))
			break ;
		if (p->desk->philo_amount == 1)
		{
			log_action(p, "has taken a fork", G);
			usleep(p->desk->die_time * 1000);
			break ;
		}
		if (take_forks(p) != 0 || eat(p) != 0 || sleep_and_think(p) != 0)
			break ;
	}
	return (NULL);
}
