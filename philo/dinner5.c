/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:30:16 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/06 15:27:20 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	try_take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		if (p->desk->fstate[p->left_fork->id] == 0
			&& p->desk->fstate[p->right_fork->id] == 0)
		{
			p->desk->fstate[p->left_fork->id] = 1;
			p->desk->fstate[p->right_fork->id] = 1;
			return (1);
		}
	}
	else
	{
		if (p->desk->fstate[p->right_fork->id] == 0
			&& p->desk->fstate[p->left_fork->id] == 0)
		{
			p->desk->fstate[p->right_fork->id] = 1;
			p->desk->fstate[p->left_fork->id] = 1;
			return (1);
		}
	}
	return (0);
}

void	lock_forks(t_philo *p)
{
	int	locked_left;
	int	locked_right;

	locked_left = 0;
	locked_right = 0;
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->left_fork->fork);
		locked_left = 1;
		pthread_mutex_lock(&p->right_fork->fork);
		locked_right = 1;
	}
	else
	{
		pthread_mutex_lock(&p->right_fork->fork);
		locked_right = 1;
		pthread_mutex_lock(&p->left_fork->fork);
		locked_left = 1;
	}
	if (locked_left)
		log_action(p, "has taken a fork");
	if (locked_right)
		log_action(p, "has taken a fork");
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
		if (check_end(p->desk))
		{
			pthread_mutex_unlock(&p->desk->butler_mutex);
			return (1);
		}
		pthread_mutex_unlock(&p->desk->butler_mutex);
		usleep(1000);
		pthread_mutex_lock(&p->desk->butler_mutex);
	}
}

void	start_trick(t_philo *p)
{
	pthread_mutex_lock(&p->desk->first_iteration_mutex);
	if (p->id % 2 == 0)
	{
		log_action(p, "is thinking");
		pthread_mutex_unlock(&p->desk->first_iteration_mutex);
		usleep(100);
	}
	else
	{
		p->desk->first_iteration = 1;
		pthread_mutex_unlock(&p->desk->first_iteration_mutex);
	}
}
