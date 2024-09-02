/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:29 by echiu             #+#    #+#             */
/*   Updated: 2024/09/02 17:34:05 by echiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time_in_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->lock);
	printf("%llu %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
}

unsigned long long	*ft_ato2long(char **str, int argc)
{
	unsigned int		i;
	unsigned int		j;
	unsigned long long	*ret;

	ret = malloc((argc - 1) * sizeof(unsigned long long));
	i = 0;
	while (++i < (unsigned int)argc)
		ret[i - 1] = 0;
	i = 0;
	while (++i < (unsigned int) argc)
	{
		j = -1;
		while (str[i][++j] != '\0')
			ret[i - 1] = ret[i - 1] * 10 + (str[i][j] - 48);
	}
	i = 0;
	while (++i < (unsigned int)argc)
	{
		if (ret[i - 1] == 0 || ret[0] > 200)
		{
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}

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

void	*addition(void *philo)
{
	t_philo	*filo;

	filo = philo;

	while (1)
	{
		if (filo->index % 2 == 0)
		{
			pthread_mutex_lock(filo->l_fork);
			print_status(filo, "has picked up left fork");

			pthread_mutex_lock(filo->r_fork);
			print_status(filo, "has picked up right fork");
		}
		else
		{
			pthread_mutex_lock(filo->r_fork);
			print_status(filo, "has picked up right fork");

			pthread_mutex_lock(filo->l_fork);
			print_status(filo, "has picked up left fork");
		}
		print_status(filo, "is eating");
		filo->last_meal = get_time_in_ms();
		usleep(filo->data->time_to_eat * 1000);

		pthread_mutex_unlock(filo->r_fork);
		print_status(filo, "has dropped right fork");

		pthread_mutex_unlock(filo->l_fork);
		print_status(filo, "has dropped left fork");
		

		print_status(filo, "is sleeping");
		usleep(filo->data->time_to_sleep * 1000);
	
		print_status(filo, "is thinking");
	}
	return (NULL);
}

void	init_data(t_data *data, unsigned long long *arr, int argc)
{
	data->nbr = 0;
	data->philo_num = arr[0];
	data->time_to_die = arr[1];
	data->time_to_eat = arr[2];
	data->time_to_sleep = arr[3];
	if (argc == 6)
		data->num_times_to_eat = arr[4];
	else
		data->num_times_to_eat = 0;
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	if (pthread_mutex_init(&data->lock, NULL) != 0)
	{
		printf("error\n");
		return ;
	}
	data->start_time = get_time_in_ms();
	while (data->nbr < data->philo_num)
	{
		pthread_mutex_init(&data->forks[data->nbr], NULL);
		data->nbr++;
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		data->philos[data->nbr].data = data;
		data->philos[data->nbr].index = data->nbr;
		data->philos[data->nbr].id = data->nbr + 1;
		data->philos[data->nbr].l_fork = &data->forks[data->nbr];
		data->philos[data->nbr].r_fork = &data->forks[(data->nbr + 1) % data->philo_num];
		data->nbr++;
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		if (pthread_create(&data->philos[data->nbr].thread, NULL, &addition, (void *)&data->philos[data->nbr]) != 0)
			printf("Ayo shit don't work\n");
		data->nbr++;
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		pthread_join(data->philos[data->nbr].thread, NULL);
		data->nbr++;
	}
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

int	main(int argc, char **argv)
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
