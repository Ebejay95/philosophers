/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputval2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:50:14 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/04 12:22:10 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_numerics(int argc, char **argv)
{
	int	valid;

	valid = 0;
	if (argc == 6 || argc == 5)
	{
		check_numeric(&valid, argv[1]);
		check_numeric(&valid, argv[2]);
		check_numeric(&valid, argv[3]);
		check_numeric(&valid, argv[4]);
		if (argc == 6)
		{
			check_numeric(&valid, argv[5]);
		}
	}
	return (valid);
}

int	check_zeros(t_desk *d, int argc)
{
	if (d->philo_amount == 0)
		return (1);
	if (d->die_time == 0)
		return (1);
	if (d->eat_time == 0)
		return (1);
	if (d->sleep_time == 0)
		return (1);
	if (argc == 6)
	{
		if (d->meal_amount == 0)
			return (1);
	}
	return (0);
}

int	retreive_input(t_desk *d, int argc, char **argv)
{
	int	check_nums;

	check_nums = check_numerics(argc, argv);
	if ((argc == 6 || argc == 5) && check_nums == 0)
	{
		d->now = my_now();
		d->end = 0;
		d->philo_amount = ft_atol(argv[1]);
		d->die_time = ft_atol(argv[2]);
		d->eat_time = ft_atol(argv[3]);
		d->sleep_time = ft_atol(argv[4]);
		if (argc == 6)
			d->meal_amount = ft_atol(argv[5]);
		else
			d->meal_amount = -1;
		if (check_zeros(d, argc))
			return (1);
		return (0);
	}
	else
		return (1);
}
