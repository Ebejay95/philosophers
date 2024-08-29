/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/29 14:51:12 by jeberle          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_desk	desk;

	if (retreive_input(&desk, argc, argv) == 0)
	{
		printf("Hello Philo\n");
		put_desk(&desk);
	}
	else
	{
		printf("No Philo\n");
	}
}
