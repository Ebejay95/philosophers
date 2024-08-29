/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/29 19:43:01 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	put_desk(t_desk *d)
{
	printf("now: %lld\n", d->now);
	printf("end: %d\n", d->end);
	printf("philo_ammount: %ld\n", d->philo_ammount);
	printf("die_time: %ld\n", d->die_time);
	printf("eat_time: %ld\n", d->eat_time);
	printf("sleep_time: %ld\n", d->sleep_time);
	if (d->meal_ammount != -1)
		printf("meal_ammount: %ld\n", d->meal_ammount);
	else
		printf("meal_ammount: undefined\n");
}

int	setup_philos_and_forks(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_ammount)
	{
		if (pthread_mutex_init(&d->forks[i].fork, NULL) != 0)
			return (1);
		d->forks[i].id = i;
		d->philos[i].id = i + 1;
		d->philos[i].meals = 0;
		d->philos[i].done = 0;
		d->philos[i].had_meal_time = d->now;
		d->philos[i].desk = d;
		d->philos[i].left_fork = &d->forks[i];
		d->philos[i].right_fork = &d->forks[(i + 1) % d->philo_ammount];
		i++;
	}
	return (0);
}

int	setup(t_desk *d)
{
	d->end = 0;
	d->forks = malloc(sizeof(t_fork) * d->philo_ammount);
	if (!d->forks)
		return (1);
	d->philos = malloc(sizeof(t_philo) * d->philo_ammount);
	if (!d->philos)
	{
		free(d->forks);
		return (1);
	}
	if (pthread_mutex_init(&d->end_mutex, NULL) != 0)
		return (1);
	setup_philos_and_forks(d);
	return (0);
}

int	end(t_desk *d)
{
	int	i;

	pthread_join(d->monitor, NULL);
	i = 0;
	while (i < d->philo_ammount)
	{
		pthread_join(d->philos[i].thread, NULL);
		pthread_mutex_destroy(&d->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&d->end_mutex);
	free(d->philos);
	free(d->forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_desk	d;

	if (retreive_input(&d, argc, argv) == 0)
	{
		if (setup(&d) != 0)
			return (1);
		//if(start(d) != 0)
		//	return (1);
		end(&d);
	}
	else
	{
		printf("invalid input\n");
		return (1);
	}
	return (0);
}
