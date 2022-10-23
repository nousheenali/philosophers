/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:58:45 by nali              #+#    #+#             */
/*   Updated: 2022/05/12 12:09:07 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philosophers.h"
/* we are unlocking the mutex after printing the death msg coz the other threads 
keep waiting for this mutex and dont finish execution.If they dont finish exec, 
threads wont be joined causing memory leaks*/

int	ft_check_philosopher_state(t_var *v)
{
	int		i;

	while (v->finished_eating == 0)
	{
		i = 0;
		while (i < v->num_of_philo)
		{
			usleep(2000);
			pthread_mutex_lock(&v->mx->state);
			if ((ft_time() - v->philosopher[i].last_meal) > v->time_to_die + 5)
			{
				if (v->philosopher[i].eat_count != 0)
				{	
					ft_print_death_msg(v, i);
					pthread_mutex_unlock(&v->mx->state);
					return (1);
				}
			}
			pthread_mutex_unlock(&v->mx->state);
			i++;
		}
		if (v->eat_flag == v->num_of_philo && v->infinite == 0)
			v->finished_eating = 1;
	}
	return (0);
}

/* if only one philo we put the thread to sleep till the philo dies
Otherwise the prog will print sleeping and thinking activity coz the philo
does not die when the prog reaches there*/
/*we have added additional usleep(9000) coze we have added a buffer of 5millisec in
ft_check_philosopher_state function*/

void	ft_sleep_think(t_philo *p)
{
	long	t;
	long	start;

	if (p->vars->num_of_philo == 1)
	{
		p->eat_count -= 1;
		usleep(p->vars->time_to_die * 1000);
		usleep(9000);
		return ;
	}
	start = p->vars->prog_start_time;
	if (p->vars->death == 0)
	{
		t = ft_timediff(start);
		printf("%ld Philosopher %d going to sleep\n", t, p->id + 1);
	}
	usleep(p->vars->time_to_sleep * 1000);
	if (p->vars->death == 0)
	{
		t = ft_timediff(start);
		printf("%ld Philosopher %d has started thinking\n", t, p->id + 1);
	}	
}

/* if only one philo then he picks up the fork and the program returns NULL.
Otherwise, the philo will wait for the 2nd fork and program hangs*/

void	ft_eat(t_philo *p, pthread_mutex_t *m, long st, int id)
{
	int		pid;
	long	t;

	pid = id + 1;
	pthread_mutex_lock(&m[p->right_fork]);
	ft_pickup_forks(st, id, p->right_fork + 1, p);
	if (p->vars->num_of_philo == 1)
		return ;
	pthread_mutex_lock(&m[p->left_fork]);
	ft_pickup_forks(st, id, p->left_fork + 1, p);
	pthread_mutex_lock(&p->mx->state);
	if (p->vars->death == 0)
	{
		t = ft_timediff(st);
		printf("\033[32m%ld Philosopher %d is eating\n\033[0m", t, pid);
		p->last_meal = ft_time();
	}
	pthread_mutex_unlock(&p->mx->state);
	if (p->vars->death == 0)
		usleep(p->vars->time_to_eat * 1000);
	if (p->vars->death == 0)
		printf("%ld Philosopher %d finished eating\n", ft_timediff(st), pid);
	pthread_mutex_unlock(&m[p->right_fork]);
	pthread_mutex_unlock(&m[p->left_fork]);
}

void	*ft_pickup_forks_eat(void *arg)
{
	t_philo			*p;
	long			st;
	pthread_mutex_t	*m;

	p = arg;
	m = p->mx->mutex;
	st = p->vars->prog_start_time;
	if (p->id % 2)
		usleep(15000);
	while (p->vars->death == 0 && p->vars->infinite == 1)
	{
		ft_eat(p, m, st, p->id);
		ft_sleep_think(p);
	}
	while (p->eat_count > 0 && p->vars->death == 0 && p->vars->infinite == 0)
	{
		ft_eat(p, m, st, p->id);
		p->eat_count -= 1;
		ft_sleep_think(p);
	}
	p->vars->eat_flag += 1;
	return (NULL);
}

int	ft_create_threads(int num_philosophers, t_var *vars)
{
	int		i;
	t_philo	*ph;

	ph = vars->philosopher;
	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_create(&ph[i].th, NULL, &ft_pickup_forks_eat, &ph[i]) != 0)
			return (1);
		i++;
	}
	ft_check_philosopher_state(vars);
	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(ph[i].th, NULL);
		i++;
	}
	return (0);
}
