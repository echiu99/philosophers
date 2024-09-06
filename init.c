/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:11:55 by echiu             #+#    #+#             */
/*   Updated: 2024/09/06 16:54:00 by echiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_data *data)
{
/*	pthread_t	t0;

	if (data->num_times_to_eat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]) != 0)
		{
			printf("Error creating monitor thread\n");
			return ;
		} */
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		if (pthread_create(&data->philos[data->nbr].thread, NULL,
				&routine, (void *)&data->philos[data->nbr]) != 0)
		{
			printf("Error creating philosopher thread\n");
			return ;
		}
		ft_usleep(1);
		data->nbr++;
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		pthread_join(data->philos[data->nbr].thread, NULL);
		data->nbr++;
	}
}

void	init_philos(t_data *data)
{
	while (data->nbr < data->philo_num)
	{
		pthread_mutex_init(&data->forks[data->nbr], NULL);
		data->nbr++;
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		data->philos[data->nbr].data = data;
		data->philos[data->nbr].index = data->nbr + 1;
		data->philos[data->nbr].l_fork = &data->forks[data->nbr];
		data->philos[data->nbr].r_fork = &data->forks[(data->nbr + 1)
			% data->philo_num];
		data->philos[data->nbr].write_lock = &data->write_lock;
		data->philos[data->nbr].dead_lock = &data->dead_lock;
		data->philos[data->nbr].meal_lock = &data->meal_lock;
		data->nbr++;
	}
}

void	init_data(t_data *data, unsigned long long *arr, int argc)
{
	data->nbr = 0;
	data->dead = 0;
	data->finished = 0;
	data->philo_num = arr[0];
	data->time_to_die = arr[1];
	data->time_to_eat = arr[2];
	data->time_to_sleep = arr[3];
	if (argc == 6)
		data->num_times_to_eat = arr[4];
	else
		data->num_times_to_eat = 0;
	if (data->philo_num <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error with the arguments\n");
		return ;
	}
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		printf("error\n");
		return ;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		printf("error\n");
		return ;
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		printf("error\n");
		return ;
	}
	data->start_time = get_time_in_us();
}
