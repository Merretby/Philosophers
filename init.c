/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:25 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/27 15:28:42 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->d_philo->forks[philo->left_fork]);
	pthread_mutex_lock(philo->d_philo->msg);
	printf("%ld ms %d has taken a fork\n", timer() - philo->d_philo->start_time, philo->id);
	pthread_mutex_unlock(philo->d_philo->msg);
	pthread_mutex_lock(&philo->d_philo->forks[philo->right_fork]);
	pthread_mutex_lock(philo->d_philo->msg);
	printf("%ld ms %d has taken a fork\n", timer() - philo->d_philo->start_time, philo->id);
	pthread_mutex_unlock(philo->d_philo->msg);
	pthread_mutex_lock(philo->d_philo->msg);
	printf("%ld ms %d is eating\n", timer() - philo->d_philo->start_time, philo->id);
	philo->tmp = timer() - philo->d_philo->start_time;
	pthread_mutex_lock(philo->d_philo->tour);
	if (philo->d_philo->n_of_meals != -1)
		philo->d_philo->stop += 1;
	pthread_mutex_unlock(philo->d_philo->tour);
	pthread_mutex_unlock(philo->d_philo->msg);
	ft_usleep(philo->d_philo->time_to_eat);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->right_fork]);
}

void	*diner(void *data_of_philo)
{
	t_philo	*philo;

	philo = (t_philo *)data_of_philo;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		take_fork_and_eat(philo);
		pthread_mutex_lock(philo->d_philo->msg);
		printf("%ld ms %d is sleeping\n", timer() - philo->d_philo->start_time, philo->id);
		pthread_mutex_unlock(philo->d_philo->msg);
		usleep(philo->d_philo->time_to_sleep);
		pthread_mutex_lock(philo->d_philo->msg);
		printf("%ld ms %d is thinking\n", timer() - philo->d_philo->start_time, philo->id);
		pthread_mutex_unlock(philo->d_philo->msg);
	}
	return (NULL);
}

void	init_philo2(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = timer();
	while(i < data->n_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->n_of_philo;
		data->philo[i].start = timer();
		data->philo[i].d_philo = data;
		pthread_create(&data->philo[i].th, NULL, &diner, &data->philo[i]);
		i++;
		usleep(100);
	}
}

int	timing(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->tour);
	if (data->stop / data->n_of_meals == data->n_of_philo)
		i = 1;
	pthread_mutex_unlock(data->tour);
	if (i == 1)
		return (0);
	return (1);
}

int	its_time_to_die(t_philo philo)
{
	if ((timer() - philo.d_philo->start_time) - philo.tmp > philo.d_philo->time_to_die)
	{
		pthread_mutex_lock(philo.d_philo->msg);
		printf("%ld ms %d died\n", timer() - philo.d_philo->start_time, philo.id);
		pthread_mutex_unlock(philo.d_philo->msg);
		return (1);
	}
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_data) * data->n_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_philo);
	data->msg = malloc(sizeof(pthread_mutex_t));
	data->tour = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->msg, NULL);
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo2(data);
	i = 0;
	while (1)
	{
		if (data->n_of_meals != -1 && timing(data) == 0)
			break ;
		if (its_time_to_die(data->philo[i]) == 1)
			break ;
		i++;
		if (i == data->n_of_philo)
			i = 0;
	}
}

void	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data = malloc(sizeof(t_data));
	data->n_of_philo = ft_atoi(av[1]);
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
	init_philo(data);
	free(data->philo);
	free(data->forks);
}
