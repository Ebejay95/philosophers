/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retreive_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:50:14 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/10 14:59:08 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	check_numeric(int *valid, char *argument)
{
	int	i;

	if (!ft_strcmp(argument, ""))
		*valid = 1;
	if (*valid == 0)
	{
		i = 0;
		while (argument[i] == 43)
			i++;
		while (*argument != '\0' && ft_isdigit(argument[i]))
			i++;
		if (argument[i] == '\0')
			*valid = 0;
		else
			*valid = 1;
	}
}

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

int	check_ranges(t_desk *d, int argc)
{
	if (d->philo_amount == 0 || d->philo_amount > 200)
		return (1);
	if (d->die_time < 60)
		return (1);
	if (d->eat_time < 60)
		return (1);
	if (d->sleep_time < 60)
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
		if (check_ranges(d, argc))
			return (1);
		return (0);
	}
	else
		return (1);
}
