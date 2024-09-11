/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:54:18 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/11 15:38:01 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	take_forks(t_philo *p)
{
	if (should_exit(p->desk))
		return (1);
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
	return (0);
}

void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}
