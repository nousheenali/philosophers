/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prcoesses_b.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:58:45 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 11:58:48 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	ft_sleep_think(t_philo *p, t_var *vars)
{
	long	t;
	long	start;
	int		i;

	i = p->id + 1;
	if (ft_one_philo_condition(vars) == 1)
	{
		usleep(vars->time_to_sleep * 1000 + 100);
		return ;
	}
	start = vars->prog_start_time;
	if (vars->death == 0)
	{
		t = ft_tdiff(start);
		printf("\033[37m%ld Philosopher %d going to sleep\n\033[0m", t, i);
	}
	usleep(vars->time_to_sleep * 1000);
	if (vars->death == 0)
	{
		t = ft_tdiff(start);
		printf("\033[37m%ld Philosopher %d started thinking\n\033[0m", t, i);
	}
}

void	ft_eat(t_philo *p, t_var *vars, long t, int id)
{
	int		i;
	long	d;

	i = id + 1;
	sem_wait(vars->forks);
	ft_pickup_forks(p, vars, 1);
	if (ft_one_philo_condition(vars) == 1)
		return ;
	sem_wait(vars->forks);
	ft_pickup_forks(p, vars, 2);
	sem_wait(vars->state);
	if (vars->death == 0)
	{
		printf("\033[32m%ld Philosopher %d is eating\n\033[0m", ft_tdiff(t), i);
		p->last_meal = ft_timestamp();
	}
	sem_post(vars->state);
	usleep(vars->time_to_eat * 1000);
	if (vars->death == 0)
	{
		d = ft_tdiff(t);
		printf("\033[37m%ld Philosopher %d finished eating\n\033[0m", d, i);
	}
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	ft_child_process(t_philo *p, t_var *vars)
{
	pthread_t	th;

	pthread_create(&th, NULL, &ft_check_philosopher_state, p);
	if (p->id % 2)
		usleep(15000);
	while (vars->death == 0 && vars->infinite == 1)
	{
		ft_eat(p, vars, vars->prog_start_time, p->id);
		ft_sleep_think(p, vars);
	}
	while (p->eat_count > 0 && vars->death == 0 && vars->infinite == 0)
	{
		ft_eat(p, vars, vars->prog_start_time, p->id);
		p->eat_count -= 1;
		ft_sleep_think(p, vars);
	}
	pthread_join(th, NULL);
	sem_post(p->vars->eatcount);
	sem_post(p->vars->finish);
	ft_sem_destroy(p->vars);
	ft_free_memory(p->vars);
	exit(0);
}

int	ft_create_processes(int num_philosophers, t_var *vars)
{
	int	i;

	i = 0;
	vars->id = (int *)malloc(num_philosophers * sizeof(int));
	if (!(vars->id))
		return (1);
	while (i < num_philosophers)
	{
		vars->id[i] = fork();
		if (vars->id[i] == -1)
			return (1);
		if (vars->id[i] == 0)
			ft_child_process(&vars->philosopher[i], vars);
		i++;
	}
	sem_wait(vars->finish);
	i = -1;
	while (++i < vars->num_of_philo)
		sem_wait(vars->eatcount);
	i = -1;
	while (++i < vars->num_of_philo)
		kill(vars->id[i], SIGKILL);
	free(vars->id);
	return (0);
}
