/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/03 15:58:52 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	try_take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		if (p->desk->fork_status[p->left_fork->id] == 0
			&& p->desk->fork_status[p->right_fork->id] == 0)
		{
			p->desk->fork_status[p->left_fork->id] = 1;
			p->desk->fork_status[p->right_fork->id] = 1;
			return (1);
		}
	}
	else
	{
		if (p->desk->fork_status[p->right_fork->id] == 0
			&& p->desk->fork_status[p->left_fork->id] == 0)
		{
			p->desk->fork_status[p->right_fork->id] = 1;
			p->desk->fork_status[p->left_fork->id] = 1;
			return (1);
		}
	}
	return (0);
}

void	lock_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->left_fork->fork);
		log_action(p, "has taken a fork");
		pthread_mutex_lock(&p->right_fork->fork);
		log_action(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&p->right_fork->fork);
		log_action(p, "has taken a fork");
		pthread_mutex_lock(&p->left_fork->fork);
		log_action(p, "has taken a fork");
	}
}

int	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->desk->butler_mutex);
	while (1)
	{
		if (try_take_forks(p))
		{
			pthread_mutex_unlock(&p->desk->butler_mutex);
			lock_forks(p);
			return (0);
		}
		pthread_mutex_unlock(&p->desk->butler_mutex);
		if (check_end(p->desk))
			return (1);
		pthread_mutex_lock(&p->desk->butler_mutex);
	}
}

void	start_trick(t_philo *p, long long eat_time)
{
	if (p->id % 2 == 0)
	{
		log_action(p, "is thinking");
		usleep(eat_time / 2);
	}
	p->desk->first_iteration = 1;
}

void	*philo(void *arg)
{
	t_philo			*p;
	t_desk			*desk;
	long long		think_time;
	t_philo_args	*args;

	args = (t_philo_args *)arg;
	p = args->philo;
	desk = args->desk;
	free(args);
	start_trick(p, desk->eat_time);
	while (1)
	{
		if (check_end(desk))
			break ;
		if (desk->philo_amount == 1)
		{
			handle_single_philosopher(p);
			break ;
		}
		if (p->desk->first_iteration && p->id % 2 != 0)
			think_in_start(p);
		if (handle_philosopher_actions(p, &think_time) != 0)
			break ;
	}
	return (NULL);
}
