/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:29 by echiu             #+#    #+#             */
/*   Updated: 2024/09/03 15:17:16 by echiu            ###   ########.fr       */
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

void	*routine(void *data_pointer) //Function too long
{
	t_philo	*philo;

	philo = data_pointer;
	while (1)
	{
		if (philo->index % 2 == 0)
		{
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

/* void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = data_pointer;
	pthread_mutex_lock(&philo->data->lock);
// Unfinished
} */

void	free_all(t_data *data)
{
	pthread_mutex_destroy(&data->lock);
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
