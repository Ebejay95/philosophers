/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:37:02 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/06 21:24:52 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	allocate_forks(t_desk *d)
{
	d->forks = malloc(sizeof(t_fork) * d->philo_amount);
	if (!d->forks)
		return (1);
	d->forks_ini = malloc(d->philo_amount * sizeof(int));
	if (!d->forks_ini)
	{
		free(d->forks);
		return (1);
	}
	return (0);
}
