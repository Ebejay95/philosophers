/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/03 15:07:27 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	start(t_desk *d)
{
	int				i;
	t_philo_args	*args;

	d->now = my_now();
	i = 0;
	while (i < d->philo_amount)
	{
		args = malloc(sizeof(t_philo_args));
		if (!args)
			return (set_end(d), 1);
		args->philo = &d->phls[i];
		args->desk = d;
		if (pthread_create(&d->phls[i].thread, NULL, philo, args) != 0)
			return (free(args), set_end(d), 1);
		i++;
	}
	if (pthread_create(&d->monitor, NULL, run_monitor, d) != 0)
		return (set_end(d), 1);
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
