/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 08:45:53 by nali              #+#    #+#             */
/*   Updated: 2022/05/09 07:41:16 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

long	ft_timestamp(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

long	ft_tdiff(long start)
{
	long	end;

	end = ft_timestamp();
	return (end - start);
}

void	ft_pickup_forks(t_philo *p, t_var *vars, int i)
{
	long	t;
	long	start;

	start = vars->prog_start_time;
	sem_wait(vars->state);
	if (vars->death == 0)
	{
		t = ft_tdiff(start);
		printf("\033[37m%ld Philosopher %d", t, p->id + 1);
		printf(" picked up fork %d\n\033[0m", i);
	}
	sem_post(vars->state);
}

void	ft_print_death_msg(t_var *vars, int i)
{
	long	timediff;

	vars->death = 1;
	if (vars->philosopher[i].eat_count != 0)
	{
		timediff = ft_tdiff(vars->prog_start_time);
		printf("\033[31m%ld Philosopher %d died\n\033[0m", timediff, i + 1);
	}
}

void	ft_free_memory(t_var *vars)
{
	free(vars->philosopher);
	free(vars->id);
}
