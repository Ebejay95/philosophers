/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:56:38 by jeberle           #+#    #+#             */
/*   Updated: 2024/08/30 15:43:28 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\x1b[31m"
# define G "\033[0;32m"
# define B "\033[0;34m"
# define Y "\033[0;93m"
# define C "\033[0;36m"
# define M "\033[0;35m"
# define W "\033[0;97m"
# define D "\x1b[0m"

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
	pthread_t		thread;
	int				id;
	t_fork			*right_fork;
	t_fork			*left_fork;
	long			meals;
	int				done;
	long			had_meal_time;
	t_desk			*desk;
	pthread_mutex_t	state_mutex;
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
	t_philo			*phls;
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	int				*fork_status;
	pthread_mutex_t	butler_mutex;
	pthread_mutex_t	end_mutex;
	int				all_ate;
};

// #############################################################################
// #                               Functions                                   #
// #############################################################################

// validators
int			ft_isdigit(int c);
int			ft_isspace(char c);
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
void		precise_sleep(long long time);
void		calculate_think_time(t_philo *p, long long *think_time);
void		think_in_start(t_philo *p);
int			check_end(t_desk *d);
void		set_end(t_desk *d);

int			eat(t_philo *p);
int			sleep_and_think(t_philo *p);
int			should_eat_urgently(t_philo *p);
void		handle_single_philosopher(t_philo *p);
int			handle_philosopher_actions(t_philo *p, long long *think_time);
int			take_forks(t_philo *p);
#endif
