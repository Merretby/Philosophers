/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:34:35 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/27 13:26:58 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void *routine(void *data_philo)
// {
// 	t_data *data;
// 	pthread_mutex_t mutex;
// 	static int i;

// 	pthread_mutex_init(&mutex, NULL);
// 	data = (t_data *)data_philo;
// 	printf("n_of_philo: %d\n", data->n_of_philo);
// 	while (i < data->n_of_philo)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		// printf("%zu %d is eating\n",data->start_time, i);
// 		i++;
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return (NULL);
// }

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

long int	timer(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long int milliseconds)
{
	long int	start;

	start = timer();
	while ((timer() - start) < milliseconds)
		usleep(60);
}
// void test()
// {
	// long int start;
	// start = timer();
	// ft_usleep(500);
	// long int end = timer();
	// printf("ft_uslep: %zu\n", end - start);
	// long int fi;
	// fi = timer();
	// usleep(500);
	// long int end2 = timer();
	// printf("usleep: %zu\n", end2 - fi);
// }

int	main(int ac, char **av)
{
	t_data	data;

	// test();
	parsing(ac, av);
	init_data(ac, av, &data);
	// start(&data);
	return (0);
}
