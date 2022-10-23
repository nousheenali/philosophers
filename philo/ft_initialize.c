/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:56:43 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 12:11:08 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_initialize_philosophers(t_var *vars, t_mutex *m)
{
	int		i;
	t_philo	*ph;
	int		n;

	n = vars->num_of_philo;
	ph = vars->philosopher;
	i = 0;
	while (i < n)
	{
		ph[i].id = i;
		ph[i].right_fork = i;
		ph[i].left_fork = ((i + 1) % n);
		ph[i].eat_count = vars->num_of_times_eat;
		ph[i].last_meal = ft_time();
		ph[i].mx = m;
		ph[i].vars = vars;
		i++;
	}
}

int	ft_initialize_mutex(int num_philosophers, t_mutex *m)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_mutex_init(&m->mutex[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_mutex_init(&m->state, NULL) != 0)
		return (1);
	return (0);
}

int	ft_destroy_mutex(t_var *vars)
{
	int	i;
	int	num_philosophers;

	num_philosophers = vars->num_of_philo;
	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_mutex_destroy(&vars->mx->mutex[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_mutex_destroy(&vars->mx->state) != 0)
		return (1);
	return (0);
}

int	ft_initialize_variables(t_var *vars, t_mutex *m, int num_philosophers)
{
	m->mutex = malloc(num_philosophers * sizeof(pthread_mutex_t));
	if (!m->mutex)
		return (1);
	if (ft_initialize_mutex(num_philosophers, m) == 1)
	{
		ft_free_memory(m);
		return (1);
	}
	vars->finished_eating = 0;
	vars->eat_flag = 0;
	vars->death = 0;
	vars->prog_start_time = ft_time();
	vars->mx = m;
	vars->philosopher = malloc(num_philosophers * sizeof(t_philo));
	if (!vars->philosopher)
	{
		ft_free_memory(m);
		return (1);
	}
	return (0);
}
