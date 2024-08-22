/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:00 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/22 18:53:10 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	int		ms;

	i = 0;
	ms = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			ms++;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	while (*str != '\0' && ft_isdigit(*str))
	{
		i = i * 10 + (*str - '0');
		str++;
	}
	if (ms != 0)
		i = (i * (-1));
	return (i);
}

int retreive_input(t_desk *d, int argc, char **argv)
{
	if (argc == 6 || argc == 5)
	{
		d->now = gettimeofday();
		d->end = 0;
		d->philo_ammount = ft_atol(argv[1]);
		d->die_time = ft_atol(argv[2]);
		d->eat_time = ft_atol(argv[3]);
		d->sleep_time = ft_atol(argv[4]);
		d->meal_ammount = ft_atol(argv[5]);
		return (0);
	}
	else
		return (0);
}

// philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	t_desk	desk;
	if(retreive_input(&desk, argc, argv))
	{
		printf("Hello Philo\n");
	}
	else
	{
		printf("No Philo\n");
	}
}
