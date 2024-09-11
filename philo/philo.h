/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:38 by jeberle           #+#    #+#             */
/*   Updated: 2024/09/11 15:40:37 by jeberle          ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				needs_forks;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long			meals;
	long			die_time;
	long			eat_time;
	int				done;
	long			had_meal_time;
	t_desk			*desk;
	pthread_mutex_t	state_mutex;
}	t_philo;

typedef struct s_philo_args
{
	t_philo		*philo;
	t_desk		*desk;
}	t_philo_args;

struct s_desk
{
	long long		now;
	int				end;
	long			philo_amount;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			meal_amount;
	pthread_mutex_t	forks[200];
	t_philo			phls[200];
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	int				monitor_should_exit;
	pthread_mutex_t	monitor_mutex;
};

// #############################################################################
// #                               Functions                                   #
// #############################################################################
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isdigit(int c);
long		ft_atol(const char *str);
long long	my_now(void);
void		check_numeric(int *valid, char *argument);
int			check_numerics(int argc, char **argv);
int			retreive_input(t_desk *d, int argc, char **argv);

void		set_end(t_desk *d);
int			setup_philos_and_forks(t_desk *d);
int			setup(t_desk *d);
int			end(t_desk *d);

void		*run_monitor(void *d_point);
void		*philo(void *p_point);
void		log_action(t_philo *p, char *action);
int			check_end(t_desk *d);
void		precise_sleep(long long time, t_desk *d);
int			check_end(t_desk *d);
void		set_end(t_desk *d);
int			should_exit(t_desk *d);
int			eat(t_philo *p);
void		handle_single_philosopher(t_philo *p);
void		wait_for_threads(t_desk *d);
void		start_trick(t_philo *p);
int			take_forks(t_philo *p);
void		release_forks(t_philo *p);
#endif
