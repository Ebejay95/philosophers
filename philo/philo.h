/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:38 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/29 21:50:26 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* Librarys*/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// #############################################################################
// #                               Stuctures                                   #
// #############################################################################

typedef struct s_desk	t_desk;

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
	long long		now;
	int				end;
	long			philo_amount;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			meal_amount;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	end_mutex;
};

// #############################################################################
// #                               Functions                                   #
// #############################################################################

// validators
int			ft_isdigit(int c);
int			ft_isspace(char c);
long		ft_atol(const char *str);
long long	current_time_in_milliseconds(void);
void		check_numeric(int *valid, char *argument);
int			check_numerics(int argc, char **argv);
int			retreive_input(t_desk *d, int argc, char **argv);

int			setup_philos_and_forks(t_desk *d);
int			setup(t_desk *d);
int			end(t_desk *d);

void		*run_monitor(void *d_point);
void		*run_philosopher(void *p_point);
#endif
