/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:47:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/30 15:07:25 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (pthread_mutex_init(&d->forks[i].fork, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&d->phls[i].state_mutex, NULL) != 0)
			return (1);
		d->forks[i].id = i;
		d->phls[i].id = i + 1;
		d->phls[i].meals = 0;
		d->phls[i].done = 0;
		d->phls[i].had_meal_time = d->now;
		d->phls[i].desk = d;
		d->phls[i].left_fork = &d->forks[i];
		d->phls[i].right_fork = &d->forks[(i + 1) % d->philo_amount];
		d->fork_status[i] = 0;
		i++;
	}
	return (0);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->forks = malloc(sizeof(t_fork) * d->philo_amount);
	if (!d->forks)
		return (1);
	d->phls = malloc(sizeof(t_philo) * d->philo_amount);
	if (!d->phls)
	{
		free(d->forks);
		return (1);
	}
	d->fork_status = malloc(sizeof(int) * d->philo_amount);
	if (!d->fork_status)
	{
		free(d->forks);
		free(d->phls);
		return (1);
	}
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0
		|| pthread_mutex_init(&d->write_mutex, NULL) != 0
		|| pthread_mutex_init(&d->butler_mutex, NULL) != 0)
		return (1);
	setup_philos_and_forks(d);
	return (0);
}

int	end(t_desk *d)
{
	int	i;

	pthread_join(d->monitor, NULL);
	i = 0;
	while (i < d->philo_amount)
	{
		pthread_join(d->phls[i].thread, NULL);
		pthread_mutex_destroy(&d->forks[i].fork);
		pthread_mutex_destroy(&d->phls[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&d->end_mutex);
	pthread_mutex_destroy(&d->write_mutex);
	pthread_mutex_destroy(&d->butler_mutex);
	free(d->phls);
	free(d->forks);
	free(d->fork_status);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	us1;
	unsigned char	us2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (-1);
	if (s2 == NULL)
		return (1);
	while (*s1 != '\0' || *s2 != '\0')
	{
		us1 = (unsigned char)*s1;
		us2 = (unsigned char)*s2;
		if (us1 != us2)
			return (us1 - us2);
		s1++;
		s2++;
	}
	return (0);
}

void	log_action(t_philo *p, char *a)
{
	pthread_mutex_lock(&p->desk->write_mutex);
	if (!check_end(p->desk) || !ft_strcmp(a, "died"))
		printf("%lld %d %s\n", my_now() - p->desk->now, p->id, a);
	pthread_mutex_unlock(&p->desk->write_mutex);
}
