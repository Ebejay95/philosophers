/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/29 21:52:49 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	start(t_desk *d)
{
	int	i;

	i = 0;
	while (i < d->philo_amount)
	{
		if (pthread_create(&d->philos[i].thread, NULL, run_philosopher, &d->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&d->monitor, NULL, run_monitor, d) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_desk	d;

	if (retreive_input(&d, argc, argv) == 0)
	{
		if (setup(&d) != 0)
			return (1);
		if (start(&d) != 0)
			return (1);
		end(&d);
	}
	else
	{
		printf("invalid input\n");
		return (1);
	}
	return (0);
}
