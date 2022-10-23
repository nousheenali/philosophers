/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:24:59 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 10:54:52 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_B_H
# define PHILOSOPHERS_B_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

struct	s_var;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	struct s_var	*vars;
}				t_philo;

typedef struct s_var
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_times_eat;
	int			death;
	int			infinite;
	long		prog_start_time;
	int			*id;
	t_philo		*philosopher;
	sem_t		*forks;
	sem_t		*state;
	sem_t		*finish;
	sem_t		*eatcount;
}				t_var;

//utils
int		ft_atoi(const char *nptr);
//main
void	*ft_check_philosopher_state(void *args);
//ft_initialize
int		ft_initialize_variables(t_var *vars);
void	ft_initialize_philosophers(t_var *vars);
void	ft_sem_destroy(t_var *vars);
int		ft_one_philo_condition(t_var *vars);
// ft_create_threads.c 
int		ft_create_processes(int num_philosophers, t_var *vars);
//ft_philo_utils
long	ft_timestamp(void);
long	ft_tdiff(long start);
void	ft_pickup_forks(t_philo *p, t_var *vars, int i);
void	ft_print_death_msg(t_var *vars, int i);
void	ft_free_memory(t_var *vars);

#endif