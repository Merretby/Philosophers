/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:35 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/11 14:54:43 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	timer(void)
{
	struct timeval	timing;
	long int		time;

	if (gettimeofday(&timing, NULL) == -1)
		return (0);
	time = (timing.tv_sec * 1000) + (timing.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int time)
{
	long long	t;

	t = timer();
	while (timer() - t < time)
		usleep(60);
}

void	desrtoy(t_data *data)
{
	pthread_mutex_destroy(data->dead_mutex);
	pthread_mutex_destroy(data->msg);
	pthread_mutex_destroy(data->tour);
	free(data->philo);
	free(data->forks);
	free(data->msg);
	free(data->dead_mutex);
	free(data->tour);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (parsing(ac, av) == 1)
	{
		data = malloc(sizeof(t_data));
		init_data(ac, av, data);
		free(data);
		data = NULL;
	}
	return (0);
}
