/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_now.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:48:17 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 14:43:34 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	my_now(void)
{
	struct timeval	now;
	long long		milliseconds;

	gettimeofday(&now, NULL);
	milliseconds = (now.tv_sec * 1000LL) + (now.tv_usec / 1000);
	return (milliseconds);
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
