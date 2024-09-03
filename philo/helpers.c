/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:47:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/09/03 16:04:20 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	end(t_desk *d)
{
	int	i;

	pthread_join(d->monitor, NULL);
	i = 0;
	while (i < d->philo_amount)
	{
		if (d->phls_ini[i])
			pthread_join(d->phls[i].thread, NULL);
		if (d->forks_ini[i])
			pthread_mutex_destroy(&d->forks[i].fork);
		if (d->phls_ini[i])
			pthread_mutex_destroy(&d->phls[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&d->end_mutex);
	pthread_mutex_destroy(&d->write_mutex);
	pthread_mutex_destroy(&d->butler_mutex);
	free(d->forks);
	free(d->forks_ini);
	free(d->phls);
	free(d->phls_ini);
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
