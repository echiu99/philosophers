/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:52 by echiu             #+#    #+#             */
/*   Updated: 2024/09/02 17:30:39 by echiu            ###   ########.fr       */
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
	pthread_t			thread;
	int					id;
	int					index;
	int					meals_eaten;
	unsigned long long	last_meal;
}	t_philo;

typedef struct s_data
{
	unsigned long long	nbr;
	unsigned long long	philo_num;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	num_times_to_eat;
	unsigned long long	start_time;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}	t_data;

#endif
