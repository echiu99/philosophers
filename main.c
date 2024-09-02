/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:49:29 by echiu             #+#    #+#             */
/*   Updated: 2024/09/02 15:25:59 by echiu            ###   ########.fr       */
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
		usleep((filo->index % 2) * 100);
		if (filo->can_pick_up_right_beer)
		{
			if (filo->index % 2 == 0)
			{
				pthread_mutex_lock(&filo->l_beer);
				print_status(filo, "has picked up left beer");

				pthread_mutex_lock(&filo->r_beer);
				print_status(filo, "has picked up right beer");
			}
			else
			{
				pthread_mutex_lock(&filo->r_beer);
				print_status(filo, "has picked up right beer");

				pthread_mutex_lock(&filo->l_beer);
				print_status(filo, "has picked up left beer");
			}
			print_status(filo, "is drinking");
			filo->last_meal = get_time_in_ms();
			usleep(filo->data->time_to_eat * 1000);

			pthread_mutex_unlock(&filo->r_beer);
			print_status(filo, "has dropped right beer");

			pthread_mutex_unlock(&filo->l_beer);
			print_status(filo, "has dropped left beer");
		}
		else
			print_status(filo, "is thinking but has no right beer to pick up");

		print_status(filo, "is sleeping");
		usleep(filo->data->time_to_sleep * 1000);
	
		print_status(filo, "is thinking");
	}
	return (NULL);
}

/* void	*addition(void *philo)
{
	t_philo	*filo;

	filo = philo;
	if (filo->index == 0)
	{
		if (filo[filo->data->philo_num - 1].f_id == 0)
		{
			pthread_mutex_lock(&filo->l_beer);
			filo->f_id++;
			printf("I am philo number %d, and I think I picked up a beer\n", filo->index);
			pthread_mutex_lock(&filo[filo->data->philo_num - 1].l_beer);
			filo[filo->data->philo_num - 1].f_id++;
			printf("I am philo number %d, and I think I picked up a second beer, number %llu\n", filo->index, filo->data->philo_num - 1);
			printf("I am philo number %d, and I will now drink\n", filo->index);
			usleep(5);
			pthread_mutex_unlock(&filo->l_beer);
			printf("I am philo number %d, and I dropped my beer\n", filo->index);
			pthread_mutex_unlock(&filo[filo->data->philo_num - 1].l_beer);
			printf("I am philo number %d, and I dropped the last person's beer, number %llu\n", filo->index, filo->data->philo_num - 1);
		}
	}
	else
	{
		if (filo[filo->index + 1].f_id == 0)
		{
			pthread_mutex_lock(&filo->l_beer);
			filo->f_id++;
			printf("I am philo number %d, and I think I picked up a beer\n", filo->index);
			pthread_mutex_lock(&filo[filo->index + 1].l_beer);
			filo[filo->data->philo_num - 1].f_id++;
			printf("I am philo number %d, and I think I picked up a second beer, number %d\n", filo->index, filo->index + 1);
			printf("I am philo number %d, and I will now drink\n", filo->index);
			usleep(5);
			pthread_mutex_unlock(&filo->l_beer);
			printf("I am philo number %d, and I dropped my beer\n", filo->index);
			pthread_mutex_unlock(&filo[filo->index + 1].l_beer);
			printf("I am philo number %d, and I dropped the next person's beer number %d\n", filo->index, filo->index + 1);
		}
	}
	return (NULL);
} */

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
	if (pthread_mutex_init(&data->lock, NULL) != 0)
	{
		printf("error\n");
		return ;
	}
	data->start_time = get_time_in_ms();
	while (data->nbr < data->philo_num)
	{
		data->philos[data->nbr].data = data;
		if (pthread_mutex_init(&data->philos[data->nbr].l_beer, NULL) != 0)
		{
			printf("error\n");
			return ;
		}
		data->philos[data->nbr].index = data->nbr;
		data->philos[data->nbr].id = data->nbr + 1;
		data->nbr++;
	}
	data->nbr = 0;
	if (data->philo_num == 1)
		data->philos[0].can_pick_up_right_beer = 0;
	else
	{
		while (data->nbr < data->philo_num)
		{
			if (data->nbr == data->philo_num - 1)
				data->philos[data->nbr].r_beer = data->philos[0].l_beer;
			else
				data->philos[data->nbr].r_beer = data->philos[data->nbr + 1].l_beer;
			data->philos[data->nbr].can_pick_up_right_beer = 1;
			data->nbr++;
		}
	}
	data->nbr = 0;
	while (data->nbr < data->philo_num)
	{
		if (pthread_create(&data->philos[data->nbr].thread, NULL, &addition, (void *)&data->philos[data->nbr]) != 0)
			printf("Ayo shit don't work\n");
		usleep(100);
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
		pthread_mutex_destroy(&data->philos[data->nbr].l_beer);
		data->nbr++;
	}
	free(data->philos);
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
