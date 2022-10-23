/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 08:45:53 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 12:09:20 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

long	ft_timediff(long start)
{
	long	end;

	end = ft_time();
	return (end - start);
}

void	ft_pickup_forks(long start, int id, int f_id, t_philo *p)
{
	long	t;

	pthread_mutex_lock(&p->mx->state);
	if (p->vars->death == 0)
	{
		t = ft_timediff(start);
		printf("%ld Philosopher %d picked up fork %d\n", t, id + 1, f_id);
	}
	pthread_mutex_unlock(&p->mx->state);
}

void	ft_print_death_msg(t_var *vars, int i)
{
	long	timediff;

	vars->death = 1;
	if (vars->philosopher[i].eat_count != 0)
	{
		timediff = ft_timediff(vars->prog_start_time);
		printf("\033[31m%ld Philosopher %d died\n\033[0m", timediff, i + 1);
	}
}

void	ft_free_memory(t_mutex *m)
{
	free(m->mutex);
}
