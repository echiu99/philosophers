/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:49:29 by echiu             #+#    #+#             */
/*   Updated: 2024/09/06 16:55:31 by echiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time_in_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((tv.tv_sec * 1000000) + (tv.tv_usec));
}

int	ft_usleep(useconds_t time)
{
	unsigned long long	start;

	start = get_time_in_us();
	while ((get_time_in_us() - start) < time)
		usleep(500);
	return (0);
}

void	print_status(t_philo *philo, char *message)
{
	unsigned long long	current_time;

	current_time = get_time_in_us();
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%llu %d %s\n", (current_time - philo->data->start_time)
		/ 1000, philo->index, message);
	pthread_mutex_unlock(&philo->data->write_lock);
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
