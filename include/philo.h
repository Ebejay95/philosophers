/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:38 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/22 18:49:01 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Librarys*/
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// #############################################################################
// #                               Stuctures                                   #
// #############################################################################

typedef struct s_desk t_desk;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_fork		*right_fork;
	t_fork		*left_fork;
	long		meals;
	int			done;
	long		had_meal_time;
	t_desk		*desk;
}	t_philo;

struct s_desk
{
	long	now;
	int		end;
	long	philo_ammount;
	long	die_time;
	long	eat_time;
	long	sleep_time;
	long	meal_ammount;
	t_fork	*forks;
	t_philo	*philos;
};

// #############################################################################
// #                               Functions                                   #
// #############################################################################

#endif
