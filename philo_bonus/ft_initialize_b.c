/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:56:43 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 12:10:21 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	ft_initialize_philosophers(t_var *vars)
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
		ph[i].eat_count = vars->num_of_times_eat;
		ph[i].last_meal = ft_timestamp();
		ph[i].vars = vars;
		i++;
	}
}

/*The prog ends either when a philo dies or whenthe philo finish eating
semaphore finish is to indicate that its time for the prog to finish exec.*/

/* The semaphore eatcount is to check if all the philo have finished eating
the required num of times(given the 6th argument). After every philo finishes 
eating this semaphore is increased by 1 */
int	ft_initialize_semaphore(t_var *vars)
{
	sem_unlink("/ph_forks");
	sem_unlink("/ph_state");
	sem_unlink("/ph_finish");
	sem_unlink("/ph_eatcount");
	vars->forks = sem_open("/ph_forks", O_CREAT, 0777, vars->num_of_philo);
	if (vars->forks == SEM_FAILED)
	{
		printf("Failed to open semphore");
		return (1);
	}
	vars->state = sem_open("/ph_state", O_CREAT, 0777, 1);
	if (vars->state == SEM_FAILED)
	{
		sem_close(vars->forks);
		printf("Failed to open semphore");
		return (1);
	}
	vars->finish = sem_open("/ph_finish", O_CREAT, 0777, 0);
	vars->eatcount = sem_open("/ph_eatcount", O_CREAT, 0777, 0);
	return (0);
}

void	ft_sem_destroy(t_var *vars)
{
	sem_close(vars->forks);
	sem_close(vars->state);
	sem_close(vars->finish);
	sem_close(vars->eatcount);
}

/*since we added a buffer of 5ms in the check_philosopher_state
function we need to do the same here otherwise the program will print
philo 1 going to sleep*/
int	ft_one_philo_condition(t_var *vars)
{
	if (vars->num_of_philo == 1)
	{
		usleep(vars->time_to_die * 1000);
		usleep(5000);
		return (1);
	}
	return (0);
}

int	ft_initialize_variables(t_var *vars)
{
	if (ft_initialize_semaphore(vars))
		return (1);
	vars->death = 0;
	vars->prog_start_time = ft_timestamp();
	vars->philosopher = malloc(vars->num_of_philo * sizeof(t_philo));
	if (!vars->philosopher)
	{
		ft_sem_destroy(vars);
		sem_unlink("/ph_forks");
		sem_unlink("/ph_state");
		sem_unlink("/ph_finish");
		sem_unlink("/ph_eatcount");
		return (1);
	}
	return (0);
}
