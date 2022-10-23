/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:24:59 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 12:08:43 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_var;

typedef struct s_mutex
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	state;
}				t_mutex;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long			last_meal;
	pthread_t		th;
	t_mutex			*mx;
	struct s_var	*vars;
}				t_philo;

typedef struct s_var
{
	int		philo_id;
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_times_eat;
	int		finished_eating;
	int		eat_flag;
	int		death;
	int		infinite;
	long	prog_start_time;
	t_philo	*philosopher;
	t_mutex	*mx;
}				t_var;

//utils
int		ft_atoi(const char *nptr);
//ft_initialize
int		ft_initialize_variables(t_var *vars, t_mutex *m, int num_philosophers);
void	ft_initialize_philosophers(t_var *vars, t_mutex *m);
int		ft_destroy_mutex(t_var *vars);
// ft_create_threads.c 
int		ft_create_threads(int num_philosophers, t_var *vars);
//ft_philo_utils
long	ft_time(void);
long	ft_timediff(long start);
void	ft_pickup_forks(long start, int id, int f_id, t_philo *p);
// void	ft_pickup_forks(long start, int id, int f_id, int dead);
void	ft_print_death_msg(t_var *vars, int i);
void	ft_free_memory(t_mutex *m);

#endif