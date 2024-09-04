/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:16:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/04 07:19:57 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->right_fork->fork);
	pthread_mutex_unlock(&p->left_fork->fork);
	pthread_mutex_lock(&p->desk->butler_mutex);
	p->desk->fstate[p->left_fork->id] = 0;
	p->desk->fstate[p->right_fork->id] = 0;
	pthread_mutex_unlock(&p->desk->butler_mutex);
}

int	should_exit(t_desk *d)
{
	int	result;

	pthread_mutex_lock(&d->end_mutex);
	result = d->end;
	pthread_mutex_unlock(&d->end_mutex);
	return (result);
}
