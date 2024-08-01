/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:25 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/01 13:33:18 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	breaker(t_data *data, int flag, int i)
{
	pthread_mutex_lock(data->msg);
	if (flag == 1)
		printf("%ld philo %d has died\n", \
			timer() - data->start_time, data->philo[i].id);
	pthread_mutex_lock(data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(data->dead_mutex);
	pthread_mutex_unlock(data->msg);
}

void	*the_tabel(void *d)
{
	int		i;
	t_data	*data;

	data = (t_data *)d;
	i = 0;
	while (1)
	{
		if (data->n_of_meals != -1 && timing(data) == 0)
		{
			breaker(data, 0, i);
			return (NULL);
		}
		if (!its_time_to_die(data->philo[i]))
		{
			breaker(data, 1, i);
			return (NULL);
		}
		i++;
		if (i == data->n_of_philo)
			i = 0;
	}
	return (NULL);
}

void	init_philo2(t_data *data)
{
	int			i;

	i = 0;
	data->start_time = timer();
	while (i < data->n_of_philo)
	{
		data->philo[i].id = i + 1;
		if (i == data->n_of_philo - 1)
		{
			data->philo[i].right_fork = i;
			data->philo[i].left_fork = (i + 1) % data->n_of_philo;
		}
		else
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = (i + 1) % data->n_of_philo;
		}
		data->philo[i].start = timer();
		data->philo[i].d_philo = data;
		pthread_create(&data->philo[i].th, NULL, &diner, &data->philo[i]);
		i++;
		usleep(60);
	}
	help_philo(data);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_data) * data->n_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_philo);
	data->msg = malloc(sizeof(pthread_mutex_t));
	data->tour = malloc(sizeof(pthread_mutex_t));
	data->dead_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->dead_mutex, NULL);
	pthread_mutex_init(data->msg, NULL);
	pthread_mutex_init(data->tour, NULL);
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo2(data);
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	desrtoy(data);
}

void	init_data(int ac, char **av, t_data *data)
{
	data->n_of_philo = ft_atoi(av[1]);
	if (data->n_of_philo == 0)
		ft_putendl_fd("number of philosophers must be greater than 0", 2);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->n_of_meals = ft_atoi(av[5]);
		if (data->n_of_meals == 0)
			ft_putendl_fd("number of meals must be greater than 0", 2);
	}
	else
		data->n_of_meals = -1;
	data->stop = 0;
	data->dead = 0;
	if (data->n_of_philo == 1)
	{
		printf("0 philo 1 has taken a fork\n");
		ft_usleep(data->time_to_die);
		printf("%d philo 1 died\n", ++data->time_to_die);
		return ;
	}
	init_philo(data);
}
