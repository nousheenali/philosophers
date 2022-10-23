/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:12:21 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 11:23:42 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start_processing(t_var *vars, t_mutex *m)
{
	int	num;

	num = vars->num_of_philo;
	if (ft_create_threads(num, vars) == 1)
	{
		ft_destroy_mutex(vars);
		ft_free_memory(m);
		free(vars->philosopher);
		return (1);
	}
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
	t_var	vars;
	t_mutex	mutex;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_inputs_check(&vars, argv, argc) == 1)
	{
		printf("Error: Invalid Inputs\n");
		return (1);
	}
	if (ft_initialize_variables(&vars, &mutex, vars.num_of_philo))
		return (1);
	ft_initialize_philosophers(&vars, &mutex);
	if (ft_start_processing(&vars, &mutex) == 1)
		return (1);
	ft_destroy_mutex(&vars);
	ft_free_memory(&mutex);
	free(vars.philosopher);
	return (0);
}
