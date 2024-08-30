/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/30 15:42:28 by jeberle          ###   ########.fr       */
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
		usleep(1000);
		pthread_mutex_lock(&p->desk->butler_mutex);
	}
}

void	start_trick(int id, long long eat_time)
{
	if (id % 2 == 0)
		usleep(eat_time / 2);
}

void	*philo(void *p_point)
{
	t_philo		*p;
	int			first_iteration;
	long long	think_time;

	first_iteration = 1;
	p = (t_philo *)p_point;
	start_trick(p->id, p->desk->eat_time);
	while (1)
	{
		if (check_end(p->desk))
			break ;
		if (p->desk->philo_amount == 1)
		{
			handle_single_philosopher(p);
			break ;
		}
		if (first_iteration && p->id % 2 != 0)
		{
			think_in_start(p);
			first_iteration = 0;
		}
		if (handle_philosopher_actions(p, &think_time) != 0)
			break ;
	}
	return (NULL);
}
