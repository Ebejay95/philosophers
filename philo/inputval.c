/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:48:17 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/29 14:50:05 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

long long	current_time_in_milliseconds(void)
{
	struct timeval	now;
	long long		milliseconds;

	gettimeofday(&now, NULL);
	milliseconds = (now.tv_sec * 1000LL) + (now.tv_usec / 1000);
	return (milliseconds);
}

void	check_numeric(int *valid, char *argument)
{
	int	i;

	if (*valid == 0)
	{
		i = 0;
		while (ft_isspace(argument[i]))
			i++;
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
