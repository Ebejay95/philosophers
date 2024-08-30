/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:35:25 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/30 15:42:35 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	eat(t_philo *p)
{
	log_action(p, "is eating");
	pthread_mutex_lock(&p->state_mutex);
	p->had_meal_time = my_now();
	pthread_mutex_unlock(&p->state_mutex);
	precise_sleep(p->desk->eat_time);
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
		p->done = 1;
	pthread_mutex_unlock(&p->state_mutex);
	pthread_mutex_unlock(&p->right_fork->fork);
	pthread_mutex_unlock(&p->left_fork->fork);
	pthread_mutex_lock(&p->desk->butler_mutex);
	p->desk->fork_status[p->left_fork->id] = 0;
	p->desk->fork_status[p->right_fork->id] = 0;
	pthread_mutex_unlock(&p->desk->butler_mutex);
	return (0);
}

int	sleep_and_think(t_philo *p)
{
	log_action(p, "is sleeping");
	precise_sleep(p->desk->sleep_time);
	log_action(p, "is thinking");
	return (0);
}

int	should_eat_urgently(t_philo *p)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&p->state_mutex);
	time_since_last_meal = my_now() - p->had_meal_time;
	pthread_mutex_unlock(&p->state_mutex);
	return (time_since_last_meal > p->desk->die_time * 3 / 4);
}

void	handle_single_philosopher(t_philo *p)
{
	log_action(p, "has taken a fork");
	precise_sleep(p->desk->die_time);
}

int	handle_philosopher_actions(t_philo *p, long long *think_time)
{
	if (take_forks(p) != 0 || eat(p) != 0)
		return (1);
	if (sleep_and_think(p) != 0)
		return (1);
	calculate_think_time(p, think_time);
	if (!should_eat_urgently(p))
		precise_sleep(*think_time);
	return (0);
}
