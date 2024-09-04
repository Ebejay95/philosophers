/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 07:37:02 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/04 07:37:12 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	allocate_forks(t_desk *d)
{
	d->forks = malloc(sizeof(t_fork) * d->philo_amount);
	d->forks_ini = calloc(d->philo_amount, sizeof(int));
	if (!d->forks || !d->forks_ini)
	{
		free(d->forks);
		free(d->forks_ini);
		return (1);
	}
	return (0);
}
