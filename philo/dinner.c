/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/09 16:28:11 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	initialize_philosopher(t_philo **p, t_desk **desk, t_philo_args *args)
{
	*p = args->philo;
	*desk = args->desk;
	free(args);
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
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(p->left_fork);
			log_action(p, "has taken a fork");
			pthread_mutex_lock(p->right_fork);
			log_action(p, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(p->right_fork);
			log_action(p, "has taken a fork");
			pthread_mutex_lock(p->left_fork);
			log_action(p, "has taken a fork");
		}
		if (eat(p) != 0 || should_exit(desk))
		{
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			break ;
		}
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		if (sleep_action(p) != 0 || should_exit(desk))
			break ;
	}
	return (0);
}

void	*philo(void *arg)
{
	t_philo	*p;
	t_desk	*desk;

	initialize_philosopher(&p, &desk, (t_philo_args *)arg);
	while (!should_exit(desk))
	{
		if (philosopher_routine(p, desk))
			break ;
	}
	return (NULL);
}
