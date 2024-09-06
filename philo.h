/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:52 by echiu             #+#    #+#             */
/*   Updated: 2024/09/06 13:03:03 by echiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data		*data;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	pthread_mutex_t		*write_lock;
	pthread_t			thread;
	int					index;
	int					dead;
	int					meals_eaten;
	unsigned long long	last_meal;
}	t_philo;

typedef struct s_data
{
	int					dead;
	int					finished;
	unsigned long long	nbr;
	unsigned long long	philo_num;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	num_times_to_eat;
	unsigned long long	start_time;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}	t_data;

int					test_params(char **str);
int					ft_usleep(useconds_t time);
void				*routine(void *philo);
void				free_all(t_data *data);
void				init_philos(t_data *data);
void				init_threads(t_data *data);
void				print_status(t_philo *philo, char *message);
void				init_data(t_data *data, unsigned long long *arr, int argc);
unsigned long long	get_time_in_us(void);
unsigned long long	*ft_ato2long(char **str, int argc);

#endif
