/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/04 07:30:08 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	initialize_philosopher(t_philo **p, t_desk **desk, t_philo_args *args)
{
	*p = args->philo;
	*desk = args->desk;
	free(args);
	start_trick(*p, (*desk)->eat_time);
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

void	handle_first_iteration(t_philo *p, t_desk *desk)
{
	pthread_mutex_lock(&desk->first_iteration_mutex);
	if (desk->first_iteration && p->id % 2 != 0)
	{
		pthread_mutex_unlock(&desk->first_iteration_mutex);
		think_in_start(p);
	}
	else
	{
		pthread_mutex_unlock(&desk->first_iteration_mutex);
	}
}

int	philosopher_routine(t_philo *p, t_desk *desk)
{
	long long	think_time;

	if (handle_single_philosopher_case(p, desk))
		return (1);
	handle_first_iteration(p, desk);
	if (handle_philosopher_actions(p, &think_time) != 0)
		return (1);
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
