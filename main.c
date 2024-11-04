/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:29 by echiu             #+#    #+#             */
/*   Updated: 2024/11/04 14:34:38 by echiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_params(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] >= '0' && str[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	*routine(void *data_pointer) // Function too long
{
	t_philo	*philo;

	philo = data_pointer;
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		if (philo->index % 2 == 0)
		{
			ft_usleep(1);
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->r_fork);
			print_status(philo, "has taken fork");
		}
		print_status(philo, "is eating");
		pthread_mutex_lock(philo->meal_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->meal_lock);
		philo->last_meal = get_time_in_us();
		ft_usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep * 1000);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *data_pointer) // Too long
{
	unsigned long long		i;
	int		all_full;
	t_data	*data;

	data = (t_data *)data_pointer;
	while (1)
	{
		i = 0;
		all_full = 1;
		while (i < data->philo_num)
		{
			pthread_mutex_lock(data->philos[i].meal_lock);
			if (get_time_in_us() - data->philos[i].last_meal
				> data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_lock);
				data->dead = 1;
				print_status(&data->philos[i], "has died");
				pthread_mutex_unlock(&data->dead_lock);
				pthread_mutex_unlock(data->philos[i].meal_lock);
				return (NULL);
			}
			if (data->num_times_to_eat > 0 && data->philos[i].meals_eaten
				< data->num_times_to_eat)
				all_full = 0;
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
		if (all_full)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	free_all(t_data *data)
{
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[data->nbr]);
		data->nbr++;
	}
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv) //Function too long
{
	t_data				data;
	unsigned long long	*arr;	

	if (argc >= 5 && argc <= 6 && test_params(argv) == 0)
	{
		arr = ft_ato2long(argv, argc);
		if (arr == NULL)
		{
			printf("Error, incorrect parameter values\n");
			free(arr);
			return (0);
		}
		init_data(&data, arr, argc);
		init_philos(&data);
		init_threads(&data);
		free_all(&data);
	}
	else if (test_params(argv) == 1)
	{
		printf("Error, incorrect parameter values\n");
		return (0);
	}
	else
	{
		printf("Error, incorrect number of parameters:\n");
		return (0);
	}
	free(arr);
	return (0);
}
