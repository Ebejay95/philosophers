/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/11 16:26:51 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	initialize_philosopher(t_philo *const *p)
{
	pthread_mutex_lock(&(*p)->state_mutex);
	(*p)->had_meal_time = my_now();
	pthread_mutex_unlock(&(*p)->state_mutex);
	start_trick(*p);
}

int	handle_single_philosopher_case(t_philo *p, t_desk *desk)
{
	if (desk->philo_amount == 1)
	{
		handle_single_philosopher(p);
		return (1);
	}
	return (0);
}

int	sleep_action(t_philo *p)
{
	log_action(p, "is sleeping");
	if (should_exit(p->desk))
		return (1);
	precise_sleep(p->desk->sleep_time, p->desk);
	if (should_exit(p->desk))
		return (1);
	else
		return (0);
}

int	philosopher_routine(t_philo *p, t_desk *desk)
{
	if (handle_single_philosopher_case(p, desk))
		return (1);
	while (!should_exit(desk))
	{
		log_action(p, "is thinking");
		if (take_forks(p) != 0)
			return (1);
		if (eat(p) != 0)
		{
			release_forks(p);
			return (1);
		}
		release_forks(p);
		if (sleep_action(p) != 0)
			return (1);
	}
	return (0);
}

void	*philo(void *arg)
{
	t_philo		*p;
	t_desk		*desk;

	p = arg;
	desk = p->desk;
	initialize_philosopher(&p);
	while (!should_exit(desk))
	{
		if (philosopher_routine(p, desk))
			break ;
	}
	return (NULL);
}
