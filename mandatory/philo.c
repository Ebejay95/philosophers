/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:00 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/22 18:24:03 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philo.h"

void ft_error(char *message)
{
	ft_printf(RED"%s\n"D, message);
	exit(EXIT_FAILURE);
}

int	main(void)
{
	ft_printf("Hello Philo\n");
	ft_error("Hello Philo");
	// check input and give to struct
}
