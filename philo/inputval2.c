/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputval2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:50:14 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/30 13:29:49 by jeberle          ###   ########.fr       */
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
		return (0);
	}
	else
		return (1);
}
