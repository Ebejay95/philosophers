/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/30 10:04:05 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
//Do not test with more than 200 philosophers.
//Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.
//Test 1 800 200 200. The philosopher should not eat and should die.
//Test 5 800 200 200. No philosopher should die.
//Test 5 800 200 200 7. No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
//Test 4 410 200 200. No philosopher should die.
//Test 4 310 200 100. One philosopher should die.
//Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable.
//Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, and so forth.
int	start(t_desk *d)
{
	int	i;

	d->now = current_time_in_milliseconds();
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
