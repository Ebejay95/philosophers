/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:52:11 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/08/30 13:34:28 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	precise_sleep(long long time)
{
	long long	start;
	long long	now;

	start = my_now();
	while (1)
	{
		now = my_now();
		if (now - start >= time)
			break ;
		usleep(100);
	}
}

void	calculate_think_time(t_philo *p, long long *think_time)
{
	long long	eat_sleep_time;
	long long	cycle_time;

	eat_sleep_time = p->desk->eat_time + p->desk->sleep_time;
	cycle_time = eat_sleep_time * 2;
	if (cycle_time >= p->desk->die_time)
		*think_time = (p->desk->die_time - p->desk->eat_time) / 2;
	else
		*think_time = (p->desk->die_time - eat_sleep_time) / 2;
	if (*think_time < 0)
		*think_time = 0;
	else if (*think_time > p->desk->die_time / 4)
		*think_time = p->desk->die_time / 4;
}

void	think_briefly(t_philo *p)
{
	long long	think_time;

	think_time = p->desk->die_time / 10;
	precise_sleep(think_time);
}

int	check_end(t_desk *d)
{
	int	end;

	pthread_mutex_lock(&d->end_mutex);
	end = d->end;
	pthread_mutex_unlock(&d->end_mutex);
	return (end);
}

void	set_end(t_desk *d)
{
	pthread_mutex_lock(&d->end_mutex);
	d->end = 1;
	pthread_mutex_unlock(&d->end_mutex);
}

int	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->desk->butler_mutex);
	while (1)
	{
		if (p->id % 2 == 0)
		{
			if (p->desk->fork_status[p->left_fork->id] == 0
				&& p->desk->fork_status[p->right_fork->id] == 0)
			{
				p->desk->fork_status[p->left_fork->id] = 1;
				p->desk->fork_status[p->right_fork->id] = 1;
				pthread_mutex_unlock(&p->desk->butler_mutex);
				pthread_mutex_lock(&p->left_fork->fork);
				log_action(p, "has taken a fork", G);
				pthread_mutex_lock(&p->right_fork->fork);
				log_action(p, "has taken a fork", G);
				return (0);
			}
		}
		else
		{
			if (p->desk->fork_status[p->right_fork->id] == 0
				&& p->desk->fork_status[p->left_fork->id] == 0)
			{
				p->desk->fork_status[p->right_fork->id] = 1;
				p->desk->fork_status[p->left_fork->id] = 1;
				pthread_mutex_unlock(&p->desk->butler_mutex);
				pthread_mutex_lock(&p->right_fork->fork);
				log_action(p, "has taken a fork", G);
				pthread_mutex_lock(&p->left_fork->fork);
				log_action(p, "has taken a fork", G);
				return (0);
			}
		}
		pthread_mutex_unlock(&p->desk->butler_mutex);
		if (check_end(p->desk))
			return (1);
		usleep(1000);
		pthread_mutex_lock(&p->desk->butler_mutex);
	}
}

int	eat(t_philo *p)
{
	log_action(p, "is eating", Y);
	pthread_mutex_lock(&p->state_mutex);
	p->had_meal_time = my_now();
	pthread_mutex_unlock(&p->state_mutex);
	precise_sleep(p->desk->eat_time);
	pthread_mutex_lock(&p->state_mutex);
	p->meals++;
	if (p->desk->meal_amount != -1 && p->meals >= p->desk->meal_amount)
		p->done = 1;
	pthread_mutex_unlock(&p->state_mutex);
	pthread_mutex_unlock(&p->right_fork->fork);
	pthread_mutex_unlock(&p->left_fork->fork);
	pthread_mutex_lock(&p->desk->butler_mutex);
	p->desk->fork_status[p->left_fork->id] = 0;
	p->desk->fork_status[p->right_fork->id] = 0;
	pthread_mutex_unlock(&p->desk->butler_mutex);
	return (0);
}

int	sleep_and_think(t_philo *p)
{
	log_action(p, "is sleeping", B);
	precise_sleep(p->desk->sleep_time);
	log_action(p, "is thinking", M);
	return (0);
}

int	should_eat_urgently(t_philo *p)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&p->state_mutex);
	time_since_last_meal = my_now() - p->had_meal_time;
	pthread_mutex_unlock(&p->state_mutex);
	return (time_since_last_meal > p->desk->die_time * 3 / 4);
}

void	*philo(void *p_point)
{
	t_philo		*p;
	int			first_iteration;
	long long	think_time;

	first_iteration = 1;
	p = (t_philo *)p_point;
	if (p->id % 2 == 0)
		usleep(p->desk->eat_time / 2);
	while (1)
	{
		if (check_end(p->desk))
			break ;
		if (p->desk->philo_amount == 1)
		{
			log_action(p, "has taken a fork", G);
			precise_sleep(p->desk->die_time);
			break ;
		}
		if (first_iteration)
		{
			think_briefly(p);
			first_iteration = 0;
		}
		if (take_forks(p) != 0 || eat(p) != 0)
			break ;
		if (sleep_and_think(p) != 0)
			break ;
		calculate_think_time(p, &think_time);
		if (!should_eat_urgently(p))
			precise_sleep(think_time);
	}
	return (NULL);
}
