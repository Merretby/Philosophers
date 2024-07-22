/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:35 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/22 12:37:38 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *data_philo)
{
	t_data *data;
	pthread_mutex_t mutex;
	static int i;
	
	pthread_mutex_init(&mutex, NULL);
	data = (t_data *)data_philo;
	printf("n_of_philo: %d\n", data->n_of_philo);
	while (i < data->n_of_philo)
	{
		pthread_mutex_lock(&mutex);
		// printf("%zu %d is eating\n",data->start_time, i);
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

// void	creat_philo(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->philo = malloc(sizeof(t_philo) * data->n_of_philo);
// 	while (i < data->n_of_philo)
// 	{
// 		data->philo[i].id = i;
// 		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
// 		pthread_join(data->philo[i].thread, NULL);
// 		i++;
// 	}
// }

size_t	timer(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void start(t_data *data)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = data->philo;
	data->start_time = timer();
	printf("start time: %zu\n", data->start_time);
	while (i < data->n_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		pthread_join(data->philo[i].thread, NULL);
		i++;
		philo[i].last_meal = timer();
		printf("last meal: %zu\n", philo[i].last_meal);
	}
	
}


int	main(int ac, char **av)
{
	t_data	data;

	parsing(ac, av);
	init_data(ac, av, &data);
	start(&data);
	return (0);
}
