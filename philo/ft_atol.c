/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:10:13 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/09 15:17:33 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	int		ms;

	i = 0;
	ms = 0;
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
