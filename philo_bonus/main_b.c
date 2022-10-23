/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:12:21 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 11:02:38 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	ft_increment_eatcount(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->vars->num_of_philo)
	{
		sem_post(p->vars->eatcount);
		i++;
	}
}

void	*ft_check_philosopher_state(void *args)
{
	t_philo	*p;

	p = args;
	while (1)
	{
		sem_wait(p->vars->state);
		if ((ft_timestamp() - p->last_meal) > p->vars->time_to_die + 5)
		{
			if (p->eat_count != 0)
			{	
				ft_print_death_msg(p->vars, p->id);
				sem_post(p->vars->finish);
				ft_increment_eatcount(p);
				ft_sem_destroy(p->vars);
				ft_free_memory(p->vars);
				exit(1);
			}
		}
		sem_post(p->vars->state);
		if (p->eat_count == 0)
			return (NULL);
	}
	return (NULL);
}

int	ft_start_processing(t_var *vars)
{
	int	num;

	num = vars->num_of_philo;
	ft_create_processes(num, vars);
	return (0);
}

int	ft_inputs_check(t_var	*vars, char **argv, int argc)
{
	vars->num_of_philo = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		vars->num_of_times_eat = ft_atoi(argv[5]);
		vars->infinite = 0;
		if (vars->num_of_times_eat <= 0)
			return (1);
	}
	else
	{
		vars->num_of_times_eat = -1;
		vars->infinite = 1;
	}
	if (vars->num_of_philo < 1)
		return (1);
	if (vars->time_to_die <= 0 || vars->time_to_eat <= 0)
		return (1);
	if (vars->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var		vars;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_inputs_check(&vars, argv, argc) == 1)
	{
		printf("Error: Invalid Inputs");
		return (1);
	}
	if (ft_initialize_variables(&vars))
		return (1);
	ft_initialize_philosophers(&vars);
	ft_start_processing(&vars);
	free(vars.philosopher);
	ft_sem_destroy(&vars);
	sem_unlink("/ph_forks");
	sem_unlink("/ph_state");
	sem_unlink("/ph_finish");
	sem_unlink("/ph_eatcount");
	return (0);
}
