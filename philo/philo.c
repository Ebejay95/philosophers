/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:19 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 15:58:34 by jeberle          ###   ########.fr       */
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
		{
			free(args);
			set_end(d);
			return (1);
		}
		i++;
	}
	if (pthread_create(&d->monitor, NULL, run_monitor, d) != 0)
		return (set_end(d), 1);
	wait_for_threads(d);
	return (0);
}

int	main(int argc, char **argv)
{
	t_desk	d;
	int		setup_result;

	if (retreive_input(&d, argc, argv) == 0)
	{
		setup_result = setup(&d);
		if (setup_result == 0)
		{
			if (pthread_mutex_init(&d.forks_mutex, NULL) != 0)
				return (1);
			if (start(&d) == 0)
			{
				while (!check_end(&d))
					usleep(1000);
				set_end(&d);
			}
			pthread_mutex_destroy(&d.forks_mutex);
		}
		end(&d);
	}
	else
	{
		printf("invalid input\n");
		return (1);
	}
	return (setup_result != 0);
}
